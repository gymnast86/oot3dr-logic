
#pragma once

#include <algorithm>
#include <vector>

template <typename T, typename Predicate>
static void erase_if(std::vector<T>& vector, Predicate pred) {
  vector.erase(std::remove_if(begin(vector), end(vector), pred), end(vector));
}

template <typename T, typename Predicate>
std::vector<T> FilterFromPool(std::vector<T>& vector, Predicate pred, bool eraseAfterFilter = false) {
  std::vector<T> filteredPool = {};
  std::copy_if(vector.begin(), vector.end(), std::back_inserter(filteredPool), pred);

  if (eraseAfterFilter) {
    erase_if(vector, pred);
  }

  return filteredPool;
}

template <typename T, typename Predicate>
std::vector<T> FilterAndEraseFromPool(std::vector<T>& vector, Predicate pred) {
  return FilterFromPool(vector, pred, true);
}

// Helper function for combining two item pools
template <typename T, typename FromPool>
void MergePools(std::vector<T>& toPool, const FromPool& fromPool)
{
    toPool.insert(toPool.end(), fromPool.begin(), fromPool.end());
}

// Same as above, but allows listing individual elements
template<typename Container, typename... Args>
void AddElementsToPool(Container& v, Args&&... args)
{
    (v.push_back(std::forward<Args>(args)), ...);
}

template <typename T>
void AddElementToPool(std::vector<T>& toPool, T element, int numberToAdd = 1)
{
    for (int i = 0; i < numberToAdd; i++)
    {
        toPool.push_back(element);
    }
}

template <typename T, typename Container>
bool ElementInPool(T element, const Container& container)
{
    return std::find(container.begin(), container.end(), element) != container.end();
}

template <typename T, typename Container>
size_t ElementCountInPool(T& element, const Container& container)
{
    return std::count(container.begin(), container.end(), element);
}

template <typename T, typename Container>
void RemoveElementFromPool( Container& container, T element, int numberToRemove = 1)
{
    for (int i = 0; i < numberToRemove; i++)
    {
        auto itr = std::find(container.begin(), container.end(), element);
        if (itr != container.end())
        {
            container.erase(itr);
        }
    }
}

template <typename First, typename... T>
bool IsAnyOf(First&& first, T&&... t)
{
    return ((first == t) || ...);
}
