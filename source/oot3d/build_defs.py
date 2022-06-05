import string
import re
import sys
import os
# Short script to hack in proper preprocessor directives for oot3d_world_graph_defs.hpp
# It expects the relative path to oot3d_world_graph_defs.hpp to be provided as the sole
# argument
def main():

    # Only build the new defs file if it's older than the pre_defs file
    pre_defs_path = sys.argv[1] + "oot3d_world_graph_pre_defs.hpp"
    defs_path = sys.argv[1] + "oot3d_world_graph_defs.hpp"
    if (os.path.getmtime(pre_defs_path) < os.path.getmtime(defs_path)):
        return None

    print("Building Logic Defs")
    directives = {}
    with open(pre_defs_path) as file:
        file_str = file.read()
        file_str = [str for str in file_str.replace('\\\n', '').split('\n') if len(str) > 0]
        lines = [line.strip() for line in file_str if line[0] == '#']
        new_lines = []
        for line in lines:
            line_parts = line.split()
            expression = ' '.join(line_parts[2:])
            expression_parts = [part for part in re.split('([ \(\)\!])', expression) if part not in [' ','']]
            for i in range(len(expression_parts)):
                if (expression_parts[i] in directives.keys()):
                    expression_parts[i] = "(" + directives[expression_parts[i]] + ")"

            expression = ' '.join(expression_parts)
            new_line = ' '.join(line_parts[0:2] + ["(",expression,")"]) + '\n'
            new_line = new_line.replace('! =', '!=')
            new_lines.append(new_line)
            line_parts = line.strip().split()
            # Don't add macros
            if '(' not in line_parts[1]:
                directives[line_parts[1]] = expression

        with open(defs_path, 'w') as out_file:
            out_file.writelines(new_lines)

main()
