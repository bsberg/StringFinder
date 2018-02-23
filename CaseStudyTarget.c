/******************************************************************************/
/*                     Target Case Study 3. Document Search                   */
/*                           @author Brian Berg                               */
/******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

# define NO_OF_CHARS 256

// CASE SENSATIVE


/**
 * generates random strings for testing
 *
 * @param char string to be filled, length of string
 * @return void
 */
void random_string(char * string, unsigned length){
	/* Seed number for rand() */
	int randomnumber;
	randomnumber = rand() % 100001;
	srand((unsigned int) time(0) + randomnumber);
   
	/* ASCII characters 65 to 121*/
	// tried to get mostly letters 
	int i;  
	for (i = 0; i < length; ++i)
	{
	  string[i] = rand() % 56 + 65;
	}

	string[i] = '\0';  
}

/**
 * Removes Spaces as well as counts size after space removal
 * ended up not using very much
 * https://stackoverflow.com/questions/1726302/removing-spaces-from-a-string-in-c
 *
 * @param source string for space removal
 * @return size of space removed string
 */
int RemoveSpaces(char* source){
	char* i = source;
	char* j = source;
	int count = 0;
	while(*j != 0)
	{
	*i = *j++;
	if(*i != ' ')
		i++;
		count++;
	}
	*i = 0;
	return count;
}


/**
 * Uses given word and searches all three files through simple argument comparing one 
 * char at a time. Once one char is matched goes into inside loop and will break if the 
 * next char is a space, EOF, or not the next letter of the seed word. 
 *
 * @param buf containing word to look up in file, file pointer 1, file pointer 2, file pointer 3, 
 * and int indicating a test or not 
 * @return void
 */
/******************************************************************************/
 									/*1*/
/******************************************************************************/
void stringMatch(char buf[16], FILE* fp1, FILE* fp2, FILE* fp3, int version){
	
	int temp;
	int size;
	int i = 0;
	int oneCount = 0;
	int twoCount = 0;
	int threeCount = 0;

	clock_t start, end;
    double cpu_time_used;

	size = RemoveSpaces(buf);

	// if we are NOT testing 
	if(version == 1){
		start = clock();
	}
	
	// for file 1
	while(1){ 
		temp = fgetc(fp1);
		if(temp == EOF){
			break;
		}
		else if(temp == buf[i]){
			while(i < size){
				temp = fgetc(fp1);
				i++;
				if(temp == ' ' || temp == EOF || temp != buf[i]){
					i = 0;
					break;
				}
				// if it gets to the end without breaking out match counter increases
				else if( temp == buf[i] && i == size-1){
					temp = fgetc(fp1);
					if(temp != ' '){
						break;
					}
					i = 0;
					oneCount++;
					break;
				}
			}
		}
	}

	// for file 2
	while(1){
		temp = fgetc(fp2);
		if(temp == EOF){
			break;
		}
		else if(temp == buf[i]){
			while(i < size){
				temp = fgetc(fp2);
				i++;
				if(temp == ' ' || temp == EOF || temp != buf[i]){
					i = 0;
					break;
				}
				// if it gets to the end without breaking out match counter increases
				else if( temp == buf[i] && i == size-1){
					temp = fgetc(fp2);
					if(temp != ' '){
						break;
					}
					i = 0;
					twoCount++;
					break;
				}
			}
		}
	}

	// for file 3 
	while(1){
		temp = fgetc(fp3);
		if(temp == EOF){
			break;
		}
		else if(temp == buf[i]){
			while(i < size){
				temp = fgetc(fp3);
				i++;
				if(temp == ' ' || temp == EOF || temp != buf[i]){
					i = 0;
					break;
				}
				// if it gets to the end without breaking out match counter increases
				else if( temp == buf[i] && i == size-1){
					temp = fgetc(fp3);
					if(temp != ' '){
						break;
					}
					i = 0;
					threeCount++;
					break;
				}
			}
		}
	}

	if(version == 1){
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

		printf("french_armed_forces.txt had: %d matches\n", oneCount);
		printf("hitchhikers.txt had: %d matches\n", twoCount);
		printf("warp_drive.txt had: %d matches\n", threeCount);
		printf("Elapsed time: %f sec\n", cpu_time_used);
	}	
	
}

/**
 * Uses the fscanf to look for regular expressions in the form of no more than 10 chars long.
 * Then uses a string compare to see if it is correct string we are looking for 
 *
 * @param buf containing word to look up in file, file pointer 1, file pointer 2, file pointer 3, 
 * and int indicating a test or not 
 * @return void
 */
/******************************************************************************/
 									/*2*/
/******************************************************************************/
void regularExpressions(char buf[16], FILE* fp1, FILE* fp2, FILE* fp3, int version){
	//char scanbuf[5];
	//int size = RemoveSpaces(buf);
	//sprintf(scanbuf,"%%%ds ", size); // records specific size of buf for scanf regExpression %3s will find any word
	// starting with the
	char temp[100];
	int oneCount = 0;
	int twoCount = 0;
	int threeCount = 0;

	clock_t start, end;
    double cpu_time_used;

    // if we are NOT testing 
    if(version == 1){
    	start = clock();
    }
  
	while(fscanf(fp1, "%10s", temp) == 1){
		if(strcmp(buf, temp) == 0){
			oneCount++;
		}
	} 

	while(fscanf(fp2, "%10s", temp) == 1){
		if(strcmp(buf, temp) == 0){
			twoCount++;
		}
	} 

	while(fscanf(fp3, "%10s", temp) == 1){
		if(strcmp(buf, temp) == 0){
			threeCount++;
		}
	} 

	// if we are NOT testing 
    if(version == 1){
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

		printf("french_armed_forces.txt had: %d matches\n", oneCount);
		printf("hitchhikers.txt had: %d matches\n", twoCount);
		printf("warp_drive.txt had: %d matches\n", threeCount);
		printf("Elapsed time: %f sec\n", cpu_time_used);
	}

}

/******************************************************************************/
 									/*3*/
/******************************************************************************/
/**
 * A utility function to get maximum of two integers 
 *
 */ 
int max (int a, int b) { return (a > b)? a: b; }
 
/**
 * The preprocessing function for Boyer Moore's
 * bad character heuristic
 *
 * @param string to be matched against text, size of that string, array for bad char rule  
 * @return void
 */
void badCharHeuristic( char *str, int size, int badchar[NO_OF_CHARS]){
    int i;
 
    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
         badchar[i] = -1;
 
    // Fill the actual value of last occurrence 
    // of a character
    for (i = 0; i < size; i++)
         badchar[(int) str[i]] = i;
}

/**
 * A pattern searching function that uses Bad Character Heuristic of Boyer Moore Algorithm 
 * only uses Bad Character also had one other rule (good suffix rule) that I did not 
 * include
 *
 * https://www.geeksforgeeks.org/pattern-searching-set-7-boyer-moore-algorithm-bad-character-heuristic/
 * for code inspiration 
 *
 * https://www.youtube.com/watch?v=4Xyhb72LCX4
 * for explination 
 *
 * @param buf containing word to look up in file, file pointer 1, file pointer 2, file pointer 3, 
 * and int indicating a test or not 
 * @return void
 */
void indexed(char buf[16], FILE* fp1, FILE* fp2, FILE* fp3, int version){

	char line[5000];
	int size;
	int oneCount = 0;
	int twoCount = 0;
	int threeCount = 0;
	
	int badchar[NO_OF_CHARS];

	clock_t start, end;
    double cpu_time_used;

    // if we are NOT testing 
    if(version == 1){
    	start = clock();
    }

	// for file 1
    while (fgets(line, sizeof(line), fp1)) {
    	int m = strlen(buf);
		int n = strlen(line);
	    /* Fill the bad character array by calling 
	       the preprocessing function badCharHeuristic() 
	       for given pattern */
	    badCharHeuristic(buf, m, badchar);
	 
	    int s = 0;  // s is shift of the pattern with 
	                // respect to text
	    while(s <= (n - m))
	    {
	        int j = m-1;
	 
	        /* Keep reducing index j of pattern while 
	           characters of pattern and text are 
	           matching at this shift s */
	        while(j >= 0 && buf[j] == line[s+j])
	            j--;
	 
	        /* If the pattern is present at current
	           shift, then index j will become -1 after
	           the above loop */
	        if (j < 0)
	        {
	            //printf("pattern occurs at shift = %d\n", s);
	 
	            /* Shift the pattern so that the next 
	               character in text aligns with the last 
	               occurrence of it in pattern.
	               The condition s+m < n is necessary for 
	               the case when pattern occurs at the end 
	               of text */
	            s += (s+m < n)? m-badchar[line[s+m]] : 1;
	            oneCount++;
	 
	        }
	 
	        else
	            /* Shift the pattern so that the bad character
	               in text aligns with the last occurrence of
	               it in pattern. The max function is used to
	               make sure that we get a positive shift. 
	               We may get a negative shift if the last 
	               occurrence  of bad character in pattern
	               is on the right side of the current 
	               character. */
	            s += max(1, j - badchar[line[s+j]]);
	    }
	}

	// for file 2
	// same as other one without all the comments
	while (fgets(line, sizeof(line), fp2)) {
		int m = strlen(buf);
		int n = strlen(line);
	    badCharHeuristic(buf, m, badchar);
	    int s = 0;  // s is shift of the pattern with 
	                // respect to text
	    while(s <= (n - m)){
	        int j = m-1;
	        while(j >= 0 && buf[j] == line[s+j])
	            j--;	 
	        if (j < 0){
	            //printf("pattern occurs at shift = %d\n", s);
	            s += (s+m < n)? m-badchar[line[s+m]] : 1;
	            twoCount++;
	        }
	        else
	            s += max(1, j - badchar[line[s+j]]);
	    }
	}

	// for file 3 
	// same as other one without all the comments
	while (fgets(line, sizeof(line), fp3)) {
		int m = strlen(buf);
		int n = strlen(line);
	    badCharHeuristic(buf, m, badchar);
	    int s = 0;  // s is shift of the pattern with 
	                // respect to text
	    while(s <= (n - m)){
	        int j = m-1;
	        while(j >= 0 && buf[j] == line[s+j])
	            j--;	 
	        if (j < 0){
	            //printf("pattern occurs at shift = %d\n", s);
	            s += (s+m < n)? m-badchar[line[s+m]] : 1;
	            threeCount++;
	        }
	        else
	            s += max(1, j - badchar[line[s+j]]);
	    }
	}


	// if we are NOT testing 
    if(version == 1){
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

		printf("french_armed_forces.txt had: %d matches\n", oneCount);
		printf("hitchhikers.txt had: %d matches\n", twoCount);
		printf("warp_drive.txt had: %d matches\n", threeCount);
		printf("Elapsed time: %f sec\n", cpu_time_used);
	}
	
}

/**
 * For testing the runtime of all 3 search methods and comapring them. Selects random strings 
 * from size 1 to 10 
 *
 * @param void 
 * @return void
 */
void runTest(FILE* fp1, FILE* fp2, FILE* fp3, int version){
	clock_t start, end;
    double cpu_time_used;
	char s[16];
	int i = 0;
	int randomnumber;

	// Test for method 1
	start = clock();
	for(i =0; i < 2000000; i++){
		//printf("%d\n", i);
    	randomnumber = rand() % 15 + 1;
    	random_string(s, randomnumber);
		stringMatch(s, fp1, fp2, fp3, version); 
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time elapsed for method 1: %f sec\n", cpu_time_used);

	// Test for method 2
	start = clock();
	for(i =0; i < 2000000; i++){
		//printf("%d\n", i);
    	randomnumber = rand() % 15 + 1;
    	random_string(s, randomnumber);
		regularExpressions(s, fp1, fp2, fp3, version); 
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time elapsed for method 2: %f sec\n", cpu_time_used);

	// Test for method 3
	start = clock();
	for(i =0; i < 2000000; i++){
		//printf("%d\n", i);
    	randomnumber = rand() % 15 + 1;
    	random_string(s, randomnumber);
		indexed(s, fp1, fp2, fp3, version); 
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time elapsed for method 2: %f sec\n", cpu_time_used);
	
}


int main(int argc, char** argv){

	srand(time(NULL));
	FILE* fp1 = fopen("sample_text/french_armed_forces.txt","r");
	FILE* fp2 = fopen("sample_text/hitchhikers.txt","r");
	FILE* fp3 = fopen("sample_text/warp_drive.txt", "r");

	char term[16]; 
	int method = 0;
	int notNumber = 1; 
	int version = 1;
	
	if(argc == 2 && strcmp(argv[1],"-t")==0){
		version = 0;
		runTest(fp1, fp2, fp3, version);
	}
	else{
		printf("Enter the search term of max length 15:\n");
		scanf("%15s", term);
		
		printf("Please enter search method number:\n 1)String Match\n 2)Regular Expression\n 3)Indexed\n");
		scanf("%d", &method);
		printf("You entered: %s\nUsing search method: %d\n", term, method);

		if(method == 1){
			stringMatch(term, fp1, fp2, fp3, version);
		}
		if(method == 2){
			regularExpressions(term, fp1, fp2, fp3, version);
		}
		if(method == 3){
			indexed(term, fp1, fp2, fp3, version);
		}
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	
}


