import os
import sys
import string
import binascii
from pathlib import Path
import glob

def main():
    path =  sys.argv[1]
    data_directory = '../romfs/'
    build_ids(path, data_directory, data_filename='item_data.yaml', type='Item', key='- name: ')
    build_ids(path, data_directory, data_filename='location_data.yaml', type='Location', key='- name: ')
    build_ids(path, data_directory, data_filename='world/*_world_graph.yaml', type='Area', key='- region_name: ')


def build_ids(main_path, data_directory, data_filename, type, key):

    # Setup paths to all the files we'll be accessing
    hpp_path = Path(main_path + type.lower() + '_id.hpp')
    cpp_path = Path(main_path + type.lower() + '_id.cpp')
    full_data_directory = Path(main_path + data_directory)

    all_file_paths = [main_path + data_directory + game_dir.stem + '/' + data_filename for game_dir in full_data_directory.iterdir() if game_dir.is_dir()]
    data_paths = []
    for file_path in all_file_paths:
        data_paths.extend([Path(file) for file in glob.glob(file_path)])

    # If any of the data files have changed since the last generation, then regenerate them
    if (not (hpp_path.exists() and cpp_path.exists())) or any([os.path.getmtime(hpp_path) < os.path.getmtime(data_file) or os.path.getmtime(cpp_path) < os.path.getmtime(data_file) for data_file in data_paths] + [True]):

        # Get all the elements in the appropriate data yaml files
        elements = []
        for data_file in data_paths:
            with open(data_file) as file:
                # The game prefix will always be at the parts index with the
                # length of the full_data_directory parts
                game_prefix = data_file.parts[len(full_data_directory.parts)]
                game_prefix = f'{game_prefix[0].upper()}{game_prefix[1:]}'
                for line in file:
                    # Only process lines that start with the key
                    if not line.startswith(key):
                        continue
                    element = line[len(key):].strip()
                    # Don't add game prefixes to the Root or Root Exits for each
                    # world
                    if element in ['Root', 'Root Exits'] and element not in elements:
                        elements.append(element)
                    else:
                        elements.append(game_prefix + ' ' + element)

        # Append the NONE and INVALID elements
        elements.insert(0, 'NONE')
        elements.append('INVALID')

        # Check if there are any new elements (instead of information of elements
        # being changed) by getting a checksum of the elements and seeing if it
        # matches the checksum in the hpp file. If it matches, then we don't
        # need to recompile
        checksum = str(binascii.crc32(''.join(elements).encode('utf8')))
        if hpp_path.is_file():
            with open(hpp_path) as hpp:
                if checksum in hpp.readline():
                    return None

        # Generate all the lists of elements we'll need. Each element will
        # need a mapping of:
        # - ID -> string
        # - string -> ID
        # - string (with underscores) -> ID
        # The last mapping is for representations of IDs in logic statements
        # where spaces are used as delimeters
        quoted_elements = ['\"' + item + '\"' for item in elements]
        quoted_underscored_elements = [item.replace(' ', '_') for item in quoted_elements]
        camel_case_elements = [item.replace(' at ', ' At ') \
                                   .replace(' on ', ' On ') \
                                   .replace(' in ', ' In ') \
                                   .replace(' of ',' Of ') \
                                   .replace(' as ', 'As ') \
                                   .replace(' the ', ' The ') \
                                   .replace(' from ', ' From ') \
                                   .replace(' ','') \
                                   for item in elements]
        name_to_id_elements = [f'{{{quoted_elements[i]}, {type}ID::{camel_case_elements[i]}}}' for i in range(len(elements))]
        name_to_id_underscore_elements = [f'{{{quoted_underscored_elements[i]}, {type}ID::{camel_case_elements[i]}}}' for i in range(len(elements))]
        id_to_name_elements = [f'{{{type}ID::{camel_case_elements[i]}, {quoted_elements[i]}}}' for i in range(len(elements))]

        print('Building ' + type + ' files')
        # Generate the {type}_id.hpp file
        with open(hpp_path, 'w') as hpp:
            hpp.write(f'// Checksum of {type}ID elements from the generation script build_ids.py: {checksum}\n' + \
                      f'// This crc32 is used to check if this file needs to be generated again\n' + \
                      f'// when data in the logic files has changed.\n')
            hpp.write(f'#pragma once\n\n#include <string>\n\nenum class {type}ID : uint32_t {{\n')
            for item in camel_case_elements:
                hpp.write('    ' + item + ',\n')
            hpp.write(f'}};\n\n{type}ID NameTo{type}ID(const std::string& name);\n\nstd::string {type}IDToName(const {type}ID& id);')

        # Generate the {type}_id.cpp file
        with open(cpp_path, 'w') as cpp:
            cpp.write(f'#include "{type.lower()}_id.hpp"\n\n' + \
                      f'#include <unordered_map>\n\n' + \
                      f'{type}ID NameTo{type}ID(const std::string& name)\n'+ \
                      f'{{\n'+ \
                      f'      static std::unordered_map<std::string, {type}ID> map = {{\n')
            for i in range(len(elements)):
                cpp.write('        ' + name_to_id_elements[i] + ',\n')
                # Only write the underscore form if it actually has underscores
                if ('_' in name_to_id_underscore_elements[i]):
                    cpp.write('        ' + name_to_id_underscore_elements[i] + ',\n')
            cpp.write(f'  	}};\n' + \
                      f'    \n' + \
                      f'    if (map.count(name) == 0)\n' + \
                      f'    {{\n' + \
                      f'          return {type}ID::INVALID;\n'
                      f'    }}\n' + \
                      f'    return map.at(name);\n' + \
                      f'}}\n\n' + \
                      f'std::string {type}IDToName(const {type}ID& id)\n'+\
                      f'{{\n'+\
                      f'    static std::unordered_map<{type}ID, std::string> map = {{\n')
            for item in id_to_name_elements:
                cpp.write('        ' + item + ',\n')
            cpp.write(f'  	}};\n' + \
                      f'    \n' + \
          	          f'    if (map.count(id) == 0)\n' + \
          	          f'    {{\n' + \
          	          f'         return \"INVALID\";\n'
          	          f'    }}\n' + \
          	          f'    return map.at(id);\n' + \
                      f'}}')


main()
