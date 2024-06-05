# RAID-Mapper
Maps raid sectors to their disk location and stripe.

RAID stands for redundant array of inexpensive disks : https://en.wikipedia.org/wiki/RAID


### INPUT

This program takes in as input T, N, C, S, and Q. T is the raid level. N is the number of disks. C is the chunk size (only matters for raid 0). S is the number of stripes. Q is the number of queries. The next Q lines take in an integer (the desired sector).


### Output

For each of the Q lines the outputs are the hard disk number ([0,N-1]) that contains the queried sector. If more than one disk has a copy of the queried sector, print the one with the smaller number (for RAID levels 1, 01, and 10).  The second number is the stripe ([0,S-1]) that contains the queried sector. The third number is the hard disk number ([0,N-1]) that contains the second copy of the queried sector for RAID levels 1, 01, and 10, or the hard disk number ([0,N-1]) that contains the parity affected by the queried sector for RAID levels 4 and 5.
