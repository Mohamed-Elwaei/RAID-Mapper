//
//  header.h
//  raid
//
//  Created by Mohammed Elwaei on 4/21/24.
//

#ifndef header_h
#define header_h

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



void level0(long sectorNumber){
    long chunkNumber = sectorNumber / chunkSize;
    long diskNumber = chunkNumber % disks;
    long stripeNumber = (chunkNumber / disks) * chunkSize + (sectorNumber % chunkSize)
    ;
    printf("%lld %lld\n", diskNumber, stripeNumber);
}

void level10(long sectorNumber, long copies){
    long pairNumber = sectorNumber;
    long diskNumberWherePairStarts = (copies * pairNumber) % disks;
    long diskNumberWherePairEnds = diskNumberWherePairStarts + copies - 1;
    long stripe = (pairNumber * copies) / disks;
    printf("%lld %lld %lld\n", diskNumberWherePairStarts, stripe, diskNumberWherePairEnds);
}


void level01(long sectorNumber, long copies){
    long startingDisk = (sectorNumber % (disks / copies));
    long endingDisk = (disks - (disks/copies) + (startingDisk % (disks/copies)));
    long stripe = (sectorNumber / (disks / copies));
    printf("%lld %lld %lld\n", startingDisk, stripe, endingDisk);
};

void level4(long sectorNumber){
    long chunkNumber = sectorNumber / chunkSize;
    long diskNumber = chunkNumber % (disks - 1);
    long stripeNumber = (chunkNumber / (disks - 1)) * chunkSize + (sectorNumber % chunkSize)
    ;
    printf("%lld %lld %lld\n", diskNumber, stripeNumber, disks - 1);
}

void level5(long sectorNumber){
    long stripe = (sectorNumber / (disks - 1));
    long diskWithParityBlock = disks - 1 - (stripe % (disks));
    long diskWithTargetSector = (diskWithParityBlock + 1 + (sectorNumber % (disks - 1))) % disks;
    printf("%lld %lld %lld\n", diskWithTargetSector, stripe, diskWithParityBlock);
}





#endif /* header_h */
