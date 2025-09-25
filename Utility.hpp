#include <chrono>
#include <thread>
#include <map>
#include <utility>


namespace qboost
{
    namespace utils
    {
        inline void Wait(long double n) {
            long k = n * 1000000;
            std::this_thread::sleep_for(std::chrono::microseconds(k));
        }
        //**
        // Sets an area from xmin->xmax and ymin->ymax to a default value.
        //  */
        template <typename T,typename X, typename st>
        inline void map2d_allocate(std::map<std::pair<T,T>,X,st>& maps, T xmin, T xmax, T ymin, T ymax, X defaultval, long double step = 1)
        {
            for (T i = xmin; i < xmax; i += step)
            {
                for (T j = ymin; j < ymax; j += step)
                {
                    std::pair<T, T> current_pos = std::make_pair(i, j);
                    maps[current_pos] = defaultval;
                }
            }
        }
        
    }
}