# cpptools
Collection of Useful tiny tools(function or class)

## [timer](https://github.com/tiny-dnn/tiny-dnn/blob/1c5259477b8b4eab376cc19fd1d55ae965ef5e5a/tiny_dnn/io/display.h)

```
std::cout << "\ntimer" << std::endl;
timer t;
for (int i = 0; i < 3; i++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << i << " ";
}
std::cout << "\ntime elapsed:" << t.elapsed() << std::endl;
```

## [parallel_for](https://github.com/tiny-dnn/tiny-dnn/blob/1c5259477b8b4eab376cc19fd1d55ae965ef5e5a/tiny_dnn/util/parallel_for.h)

```
std::cout << "\nparallel_for" << std::endl;
int n = 8;
std::vector<int> ivec(n);
timer t;

std::cout << "non-parallel-for: ";
t.restart();
for (int i = 0; i < n; i++) {
    ivec[i] += 1;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
std::cout << t.elapsed() << "s" << std::endl;

std::cout << "parallel-for: ";
t.restart();
for_i(ivec.size(), [&](size_t i){
    ivec[i] += 1;
    std::this_thread::sleep_for(std::chrono::seconds(1));
});
std::cout << t.elapsed() << "s" << std::endl;
```


### [ThreadPool](https://github.com/progschj/ThreadPool)

```
std::cout << "\nThreadPool" << std::endl;
int task_cnt = 80;
int thread_cnt = 16;

ThreadPool pool(thread_cnt);
std::vector< std::future<int> > results;

timer t;
for (int i = 0; i < task_cnt; ++i) {
    results.emplace_back(
            pool.enqueue([i] {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return i * i;
            })
    );
}

for (int i = 0; i < task_cnt; i++) {
    results[i].wait();
}

std::cout << "task cnt:" << task_cnt << ", thread cnt:" << thread_cnt <<
          ", total time:" << t.elapsed() << std::endl;

std::cout << "first three: ";
for (int i = 0; i < 3; i++) {
    std::cout << results[i].get() << " ";
}
std::cout << std::endl;
```

### [pystring](https://github.com/imageworks/pystring)

```
std::string s = "\t Hello,World ";
auto s_strip = pystring::strip(s);
std::cout << s_strip << std::endl;

std::vector<std::string> res;
pystring::split(s_strip, res, ",");
std::cout << pystring::join("|", res) << std::endl;
```