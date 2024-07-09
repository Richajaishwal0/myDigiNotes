#include <stdio.h>
#include <string.h>

char round_keys[16][48]; 

void shift_left_once(char *key_chunk, int len) {
    char temp = key_chunk[0];
    for (int i = 1; i < len; i++) {
        key_chunk[i - 1] = key_chunk[i];
    }
    key_chunk[len - 1] = temp;
}

void shift_left_twice(char *key_chunk, int len) {
    shift_left_once(key_chunk, len);
    shift_left_once(key_chunk, len);
}

void generate_keys(char *key) {
    int pc1[56] = {
        57,49,41,33,25,17,9,
        1,58,50,42,34,26,18,
        10,2,59,51,43,35,27,
        19,11,3,60,52,44,36,
        63,55,47,39,31,23,15,
        7,62,54,46,38,30,22,
        14,6,61,53,45,37,29,
        21,13,5,28,20,12,4
    };

    int pc2[48] = {
        14,17,11,24,1,5,
        3,28,15,6,21,10,
        23,19,12,4,26,8,
        16,7,27,20,13,2,
        41,52,31,37,47,55,
        30,40,51,45,33,48,
        44,49,39,56,34,53,
        46,42,50,36,29,32
    };
	// perm_Key holds the key after pc1
	// pc1 discards the every 8th and its multiple bits counted from 1
    char perm_key[56];
    memset(perm_key, 0, sizeof(perm_key));
	

    for (int i = 0; i < 56; i++) {
        perm_key[i] = key[pc1[i] - 1]; // since 57th bit(counted from 1) of key is first bit of key after pc1
    }
	
	// perm_key now hold the keys after pc1
    char left[28], right[28];

    memcpy(left, perm_key, 28); // keeping first 28 bits in left array
    memcpy(right, perm_key + 28, 28); // keping next 28 bits in right array

	// now we got C0,D0

    for (int i = 0; i < 16; i++) {
		// for round 1,2,9,16 left shift is once otherwise left shift=2
        if (i == 0 || i == 1 || i == 8 || i == 15) {
            shift_left_once(left, 28);
            shift_left_once(right, 28);
        } else {
            shift_left_twice(left, 28);
            shift_left_twice(right, 28);
        }

        char combined_key[56];
        memcpy(combined_key, left, 28);
        memcpy(combined_key + 28, right, 28);

		// now we got the shifted combined key
		

		// taking through pc2 operation
        for (int j = 0; j < 48; j++) {
            round_keys[i][j] = combined_key[pc2[j] - 1];
        }

		// now we got 48 bit round keys


		// printing the 48 bit round keys in the format 6-6-6-6-6-6-6-6 bits
        printf("Key %d: ", i + 1);
        for (int j = 0; j < 48; j++) {
            if (j > 0 && j % 6 == 0) {
                printf(" ");
            }
            printf("%c", round_keys[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char key[] = "0110110001101100011011001110111110101010111100111100111010101010";
	if (strlen(key) != 64) {
		printf("The key length must be equal to 64");
		return -1;
	}
    generate_keys(key);
    return 0;
}
