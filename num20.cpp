#include <iostream>
#include <time.h>
#include <stdint.h>

int get_num()
{
    // I assume this should return 0..999
    return rand() % 1000;
}

void print_nums(int nums[])
{
    std::cout << "        ";
    for (int i = 0; i < 20; i++)
    {
        if (nums[i] >= 0)
        {
            std::cout << nums[i] << "  ";
        }
        else
        {
            std::cout << "...  ";
        }
    }
    std::cout << std::endl;
}

int find_optimal_pos(int n, int nums[])
{
    int apos = -1;
    int aval = 0;

    int bpos = 20;
    int bval = 1000;

    for (int i = 0; i < 20; i++)
    {
        if (nums[i] >= 0)
        {
            // find position of largest number smaller than n
            if (nums[i] <= n)
            { 
                 apos = i;
                 aval = nums[i];
            }

            // find position of smallest number larger than n
            if (nums[i] >= n && bpos > i)
            {
                bpos = i;
                bval = nums[i];
            }
        }
    }

    if (bpos <= apos + 1)
    {
        // no room
        return -1;
    }

    apos++;

    // calculate a value in the range of [apos,bpos)
    
    int npos = (((n - aval) * (bpos - apos)) / (bval - aval)) + apos;
    return npos;
}

int run_game()
{
   int nums[20];

   for (int i = 0; i < 20; i++)
   {
       nums[i] = -1;
   }

   for (int i = 0; i < 20; i++)
   {
      int32_t n = get_num();
      int p = find_optimal_pos(n, nums);
      if (p >= 0 && p < 20)
      {
          nums[p] = n;
      }
      else
      {
          //std::cout << i << "  " << n << "        ";
          //print_nums(nums);
          return i;
      }
   }

    //print_nums(nums);
    return 20;
}

int main()
{
    uint32_t trials = 0;
	uint32_t t0;
	
    uint32_t failcount = 0;
    uint32_t successcount = 0;

    srand(time(NULL));

    while (trials < 1000000000)
	{
	    for (t0 = 0; t0 < 1000000; t0++)
	    {
            trials++;
            int res = run_game();
            if (res == 20)
            {
                successcount++;
            }
            else
            {
                failcount++;
            }
		}
		float rate = successcount;
		rate /= failcount;
		rate *= 100.0;
		std::cout << rate << std::endl;
    }

    return 0;
}

