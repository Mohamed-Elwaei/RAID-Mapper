//
//  main.c
//  RAID
//
//  Created by Mohammed Elwaei on 4/5/24.

/*
 T : Raid Level
 N : No. of hard disks.
 C : size of the chunks.
 S : sectors per disk.
 Q : No. of Queries.
 

 Output should be:
 Disk No., Stripe (row), Disk no. for second copy (Raid levels 1,10,01).
 */

#include <stdio.h>
#include <string.h>
#define long long long int
long disks, chunkSize, stripes, queries;
char raidLevel[3];



/*
 Level 0 is not too difficult to calculate.
 First we figure out which chunk the sector we want is in.
 We have disks / chunkSize chunks. Our sector will be in chunk sectorNumber / chunksize.
 
 Then we calculate which disk our chunk and our target sector is on. We do that by using the modulo operator.
 We mod the chunkNumber with the columns (disks) we have. diskNumber = chunkNumber % disks;
 
 To get the stripe our target sector is in, first we have to calculate at which row our chunk starts.
 We calculate the row where our chunk starts by dividing the chunk by the disk number, taking the floor of that division,
 and then multiplying the result by the chunksize: stripe = (chunkNumber / disks) * chunkSize
 
 After getting the row or stripe where our chunk starts,
 we add the offset of our sector in the chunk to the row. stripe = stripe + (sectorNumber % chunkSize)
 
*/
void level0(long sectorNumber){

    long chunkNumber = sectorNumber / chunkSize;
    long diskNumber = chunkNumber % disks;
    long stripeNumber = (chunkNumber / disks) * chunkSize + (sectorNumber % chunkSize)
    ;
    printf("%lld %lld\n", diskNumber, stripeNumber);
}



/*
Level 10 and level 1 will be calculated in the same manner.
This function takes in 2 inputs: sector Number, and how many copies of that sector we have.
For this project, we will always have 2 copies. But I beleive this works if we had 3 or more copies of each sector.
In the visualization, our copies will be on the same row, on adjacent columns.
Our pair number will be the same as the sector number.
 
We calculate which disk (column) our pair is in by multiplying the pair number by the number of copies
 (always 2 in this project) and then taking the remainder when divided by the number of disks (columns).
 
 To get the disk where our pair ends and our copy stored we add the no. of copies and subtract by one
 to get the disk where the copy is stored (in this project we always add 1).
 
 The stripe (row) can be calculated by multiplying the pair number by 2, dividing by the no. of disks (columns).
 
 We then print the 3 required values.
*/

void level10(long sectorNumber, long copies){
    long pairNumber = sectorNumber;
    long diskNumberWherePairStarts = (copies * pairNumber) % disks;
    long diskNumberWherePairEnds = diskNumberWherePairStarts + copies - 1;
    long stripe = (pairNumber * copies) / disks;
    printf("%lld %lld %lld\n", diskNumberWherePairStarts, stripe, diskNumberWherePairEnds);
}



/*
 In raid level 01, the sectors are stored in the left half and mirrored in the right half.
 In this project, we always have 2 copies of each sector.
 To get the stripe (row) with both copies, we divide the sector number with half the amount of disks we have and floor the result: stripe = (sectorNumber / (disks / copies));
 
 To get the disk no. for the first copy, we modulo the sector number with hald the amount of disks: startingDisk = (sectorNumber % (disks / copies));
 To get the disk no. for the second copy, we offset the second half by the disk no. for the first copy.
 
 This would be the same as calling level0 for the left and right half of the matrix in the visualization.
 
*/
void level01(long sectorNumber, long copies){
    long startingDisk = (sectorNumber % (disks / copies));
    long endingDisk = disks - (disks/copies) + (startingDisk);
    long stripe = (sectorNumber / (disks / copies));
    printf("%lld %lld %lld\n", startingDisk, stripe, endingDisk);
};



/*
level 4 is identical to level 0, the only difference is the number of disks is reduced by 1 due to the parity disk.
We always print the last disk as the one owning the copy of the sector.
*/
void level4(long sectorNumber){
    long chunkNumber = sectorNumber / chunkSize;
    long diskNumber = chunkNumber % (disks - 1);
    long stripeNumber = (chunkNumber / (disks - 1)) * chunkSize + (sectorNumber % chunkSize)
    ;
    printf("%lld %lld %lld\n", diskNumber, stripeNumber, disks - 1);
}



/*
 This required the most effort.
 The stripe (row) can be easily calculated by dividing the sector Number by the number of disks (columns) - 1 and flooring the result. stripe = (sectorNumber / (disks - 1));
 
 We then need to find out which disk our parity block is in.
 Our parity block disk starts from the rightmost position and goes left by 1 as it descends through each row.
 We calculate the disk which contains our parity block by subtracting the no. of disks - 1 to make it 0 indexed, then subtracting by the stripe moduloed with the number of disks we have.
 We calculate the disk which contains our target sector by offseting from the right of the parity block.
 We add 1 + the row offset of our sector + the disk with our parity block and modulo the result with the number of disks we have.
 
*/
void level5(long sectorNumber){
    long stripe = (sectorNumber / (disks - 1));
    long diskWithParityBlock = disks - 1 - (stripe % (disks));
    long diskWithTargetSector = (diskWithParityBlock + 1 + (sectorNumber % (disks - 1))) % disks;
    printf("%lld %lld %lld\n", diskWithTargetSector, stripe, diskWithParityBlock);
}






int main(int argc, const char * argv[]) {
    //Get the input. The raid level (0,1,01,10,4,5), How many disks, The size of each chunk, How many stripes (rows) we have, And how many queries
    scanf("%s %lld %lld %lld %lld", raidLevel, &disks, &chunkSize, &stripes, &queries);

    
    //Loop through each query
    while (queries--) {
        
        //Get the sector number
        long sectorNumber;
        scanf("%lld", &sectorNumber);
        
        //Call one of the helper functions depending on the raid level
        if (strcmp(raidLevel, "0") == 0)
            level0(sectorNumber);
        
        else if ((strcmp(raidLevel, "1") == 0) || (strcmp(raidLevel, "10") == 0))
            level10(sectorNumber, 2);
        
        else if (strcmp(raidLevel, "01") == 0)
            level01(sectorNumber, 2);
        
        else if (strcmp(raidLevel, "4") == 0)
            level4(sectorNumber);
        
        else if (strcmp(raidLevel, "5") == 0)
            level5(sectorNumber);
    }
    
}
