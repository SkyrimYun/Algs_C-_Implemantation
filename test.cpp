#include <vector>

vector<int> findShortPaht(vector<Road> roads, int start_road, int end_road)
{
    for (each next road in roads[start_road])
    {
        vector<PQ> possible_paths - push the next road to a vector
    }

    while (possible_paths not empty)
    {
        pop out path i in possible_paths

            for (every next road from path i)
        {

            update the path to possible_path if (next_road == end_road)
            {
                return the current path from start to end
            }
        }
    }
}