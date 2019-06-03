//
// Created by lilin on 19-5-25.
//

#ifndef STRSIM_PARALLEL_FOR_H
#define STRSIM_PARALLEL_FOR_H


#include <cassert>
#include <cstdio>
#include <limits>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <thread>
#include <future>


struct blocked_range {
    typedef size_t const_iterator;

    blocked_range(size_t begin, size_t end) : begin_(begin), end_(end) {}
    const_iterator begin() const { return begin_; }
    const_iterator end() const { return end_; }

private:
    size_t begin_;
    size_t end_;
};


template <typename Func>
inline void parallel_for(size_t begin,
                         size_t end,
                         const Func &range_func) {
    assert(end >= begin);
    size_t nthreads = std::thread::hardware_concurrency(); // 核的数目
    size_t blockSize = (end - begin) / nthreads;
    if (blockSize * nthreads < end - begin) blockSize++;

    std::vector<std::future<void> > futures;

    size_t blockBegin = begin;
    size_t blockEnd = blockBegin + blockSize;
    if (blockEnd > end) blockEnd = end;

    for (size_t i = 0; i < nthreads; i++) {
        futures.push_back(
                std::move(
                        std::async(std::launch::async, [blockBegin, blockEnd, &range_func]
                        {
                            range_func(blocked_range(blockBegin, blockEnd));
                        })));

        blockBegin += blockSize;
        blockEnd = blockBegin + blockSize;
        if (blockBegin >= end) break;
        if (blockEnd > end) blockEnd = end;
    }

    for (auto &future : futures) future.wait();
}


template <typename Func>
inline void for_i(size_t size, Func elem_func) {
    parallel_for(0u, size, [&](const blocked_range &r) {
        for (size_t i = r.begin(); i < r.end(); i++) {
            elem_func(i);
        }
    });
}


#endif //STRSIM_PARALLEL_FOR_H
