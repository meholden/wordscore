#include <stdio.h>
#include <stdlib.h>

// by Mike Holden 12/2015
/* From a photo on facebook:
	if a b c d e f g h i j k l m n o p q r s t u v w x y z
	equals 1 2 3 4 5 6 7 8 9 ... 26
	search a dictionary file for words that add up to 100.
	  attitude=100
	  knowledge=96
	  hardwork=98
*/

int main(int argc, char *argv[]) {
	FILE * fp, *fw;
	int iline=0,ended=0,gotword=0, iw=0, score=0, perfcount=0;
	char c=2,wrd[50];
	
	fp = fopen("en_US.dic","r");
	fw = fopen("perfectwords.txt","w");
	
	printf("Beginning the search!\r\n");
	
	while ((iline>-1)&& (c != EOF)){
		c = getc(fp);
		//printf("%c",c);
		if ((c >= 'a') && (c<='z')) { 
		// add up lowercase letter scores
			if (ended==0) {
				//printf("%c",c);
				score+= (c-'a')+1;
				wrd[iw]=c;
				iw++;
				if (iw>=50) {
					iw=0;
				}
				gotword=1;
			}
		} else {  
		// look for end of line or / that ends word
		// print words with scores that are "perfect"
			ended=1;
			if (c==10){ // end of line
				ended=0; // next char is beginning
				iline++;
				//printf("%d\r\n",iline);
				if (gotword==1) {
					//printf(" %d \r\n", score);
					gotword=0;
					if (score==100) {
						wrd[iw]=0; // end string
						fprintf(fw,"%s\r\n",wrd);
						perfcount++;
					}
					score=0;
					iw=0;
				}
			}
		}
	}
	printf("found %d perfect words\r\n",perfcount);
	fclose(fp);
	fclose(fw);
	return 0;
}
