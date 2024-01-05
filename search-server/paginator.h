#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end);

    Iterator begin() const;

    Iterator end() const;

    size_t size() const;

private:
    Iterator begin_, end_;
}; 

template <typename Iterator>
IteratorRange<Iterator>::IteratorRange(Iterator begin, Iterator end) 
     : begin_(begin), end_(end)
{
}

template <typename Iterator>
Iterator IteratorRange<Iterator>::begin() const {
    return begin_;
}

template <typename Iterator>
Iterator IteratorRange<Iterator>::end() const {
    return end_;
}

template <typename Iterator>
size_t IteratorRange<Iterator>::size() const {
    return distance(begin_, end_);
}

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t page_size);

    auto begin() const;

    auto end() const;

    size_t size() const;

private:
    std::vector<IteratorRange<Iterator>> pages_;
}; 

template <typename Iterator>
Paginator<Iterator>::Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (auto it = begin; it < end; it += page_size){
        Iterator page_begin = it;
        Iterator page_end = next(it, std::min(page_size, static_cast<size_t>(distance(it, end))));
        pages_.push_back(IteratorRange(page_begin, page_end));
    } 
}

template <typename Iterator>
auto Paginator<Iterator>::begin() const {
    return pages_.begin();
}

template <typename Iterator>
auto Paginator<Iterator>::end() const {
    return pages_.end();
}

template <typename Iterator>
size_t Paginator<Iterator>::size() const {
    return pages_.size();
}

template <typename DocumentIterator>
std::ostream& operator<<(std::ostream& out, const IteratorRange<DocumentIterator> range){
    for (auto it = range.begin(); it != range.end(); ++it){
        out << *it;
    }
    return out;
}

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}