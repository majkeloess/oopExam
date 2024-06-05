#include <iostream>
#include <string>
#include <thread>
#include <mutex>
 
thread_local int rage = 1; 
std::mutex cout_mutex; // for cout sync
 
void change_rage(const std::string& thread_name)
{
    for(auto i = 0; i < 10; ++i)
    {
        if(thread_name == "a")
            ++rage; // modifying outside a lock is okay; this is a thread-local variable
        else
            --rage; // modifying outside a lock is okay; this is a thread-local variable
    }   
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "Rage counter for " << thread_name << ": " << rage << '\n';
}
 
int main()
{
    std::thread a(change_rage, "a"), b(change_rage, "b");
 
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Rage counter for main: " << rage << '\n';
    }
 
    a.join();
    b.join();
}