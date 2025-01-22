#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int strLen(char *str){
	int length = 0;
	while(str[length] != '\0'){
		length++;
	}
	return length;
}

void *msSetString(char str[]){
	long int strLength = strLen(str);
	char strNoNull[strLength];/*allocate space for only the string without the Null terminator*/
	int i = 0;
	for(i = 0; i < strLength; i++){ /*copies only the characters to stringNoNUll*/
		strNoNull[i] = str[i];
	}
	void *ptr = malloc(sizeof(long int) + (strLength * sizeof(char)));/*allocates memory for the new msString*/
	void *ptrO = ptr;/*sets the memory address of the pointer to be outputted to the same as the allocated memory*/
	if(ptr == NULL){/*checks if memory is allocated and exits to failure if it hasnt*/
		printf("memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	*(long int *)ptr = strLength; /*stores the lenth of the msString in a long int at the start of the memory allocated*/
	strcpy((char *)(ptr + sizeof(long int)), strNoNull ); /*copies the string to memory immediately after the long int*/
	return ptrO;
}

char *msGetString(void *ptr){
	long int strLength;
	if(ptr == NULL){/*checks to see if the pointer is valid*/
		msError("This is an invalid pointer");
	}
	
	strLength = *(long int *)(ptr);/*finds length of msString*/
	char *str = malloc((strLength + 1) * sizeof(char));/*allocats memory for the string outputted*/
	if (str == NULL){
		msError("Memory allocation failure");
	}
	ptr +=sizeof(long int);/*moves pointer to the start of the string*/
	int i = 0;
	for(i = 0; i< strLength; ++i){/*iterates through the memory and allocates characters from the msString into str*/
		str[i] = *(char *)ptr;
		ptr +=sizeof(char);
	}
	str[i] = '\0';/*adds a null character at end*/
	return str;
}

int msCopy(void**msStrPtr, void *msString){
	long int originalStrLen;
	long int copiedStrLen = *(long int*)(msString);/*finds the length of the copied msString*/
	if(*msStrPtr != NULL){/*checks id the string to be copied to has any allocated memory*/
		originalStrLen = *((long int*)*msStrPtr);/*stores length of the destination string*/
	}else{	/*if there is no data present at the pointers location then a size of 0 is allocated*/
		originalStrLen = 0;
	}
	void *ptr = realloc(*msStrPtr, 8+ (sizeof(char) * copiedStrLen));/*resizes memory to fit new msString*/	
	if(ptr == NULL){
		msError("Memory allocation failed");
	}
	*msStrPtr = ptr;/*adjucts the original pointer to match the new location*/	
	memcpy(*msStrPtr, msString, 8 + (sizeof(char) * copiedStrLen));/*overwrites the original string*/	
	return 0;	
}

int msConcatenate(void **ptrMsString1, void *msString2){
	
 	long int msStr1Len = *(long int *)*ptrMsString1; /*finds the lengths of both msStrings*/
	long int msStr2Len = *(long int *)msString2;
	long int newStrLen = (msStr1Len + msStr2Len);/*finds the total length of the new msString*/
	void *ptr = realloc(*ptrMsString1, 8 + ((sizeof(char) * newStrLen)));/*allocates memory for the new msString*/
	if(ptr == NULL){
		msError("Memory allocation failed");
	}
	
	*(long int *)ptr = newStrLen;/*adjusts the size of the string to refect concatanation*/
	ptr =(char *)ptr +(8 + (sizeof(char)*msStr1Len));/*changes pointer location to after the long int*/
	char *string2 = msGetString(msString2);/*finds the string of the second msString*/
	char msString2NoNull[msStr2Len];/*allocates room for string without the null terminator*/
	int i = 0;
	for(i = 0; i < strLen(string2);i++){/* removes the Null character from the string*/
		msString2NoNull[i] = string2[i];
	}
	memcpy(ptr, msString2NoNull, sizeof(char) *(msStr2Len));/*copies the new string over into the memory contiguously after the original msString*/
	free(string2);
	return 0;
	
}

int msLength(void *msString){
	long int stringLengthLong = *(long int *)msString; /*finds the length in the form of a long int*/
	int stringLength = 0;
	if(stringLengthLong > INT_MAX){ /*checks to see if the long int can be converted into an int*/
		msError("Long int is too long to be represented as integer");
	}else{
		stringLength = (int)stringLengthLong;/*converts the long int to an integer*/
	}
	return stringLength;

}

int msCompare(void *msString1, void *msString2){
	if(*(long int *)msString1 != *(long int *)msString2){/*checks to see if the strings are the same length*/
		return 1;/*returns failure if they aren't*/
	}
	long int strLength = *(long int *)(msString1);/*stores the length of the strings*/
	int i = 0;
	msString1+=8;/*iterates both pointers by 8 to skip past the long int*/
	msString2+=8;
	for(i = 0; i< strLength; i++){/*compares each character in the strings to each other*/
		if(*(char *)msString1 != *(char *)msString2){
			return 1;/*returns failure if the chars dont match*/
			
		}
		msString1+=sizeof(char);/*iterates the pointers through the characters*/
		msString2+=sizeof(char);	
	}	
	return 0;/*returns successful*/

}

int msCompareString(void *msString, char string[]){
	char msStringString;
	int flag = 0;
	int msStringLength = (int)*(long int *)msString;/*stores the length of the msString*/
	int i = 0;
	msString+=8;
	if(msStringLength != strLen(string)){/*checks to see if the two strings are the same length*/
		return 1;/*returns failure if they aren't*/ 
	}
	
	for(i = 0; i < msStringLength; i++){/*compares each character in the string*/ 
		if(*(char *)msString != string[i]){
			return 1;/*returns failure if they are different*/
		}
		msString+=sizeof(char); /*iterates pointer by the size of a char*/
	}
	return 0;

}

msError(char string[]){
	printf("%s", string);/*prints an error message and exits with failure*/
	exit(EXIT_FAILURE);
}
