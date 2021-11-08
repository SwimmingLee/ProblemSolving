/*
  DO NOT USE ANY GLOBAL VARIABLE OR STATIC VARIABLE IN USER CODE.
  ONLY LOCAL VARIABLE AND CONSTANT ARE ALLOWED. ALSO, IT IS NOT
  ALLOWED TO ALLOCATE MEMORY BY CALLING malloc FUNCTION OR 'new' KEYWORD.
*/

// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.
//
// bool mstrcmp(unsigned char *a, unsigned char *b) {
//     while(*a && *a == *b)
//         ++a, ++b;
//     return *a == *b;
// }
//
// int mstrlen(unsigned char *a) {
//     int len = 0;
//     while (*a)
//         ++a, ++len;
//     return len;
// }

extern bool memread(unsigned char dest[], int pos, int len);
extern bool memwrite(unsigned char src[], int pos, int len);

#define MAXLEN 12

int getEmptySapce() {
	unsigned char c;
	int pos;
	for (pos = 0; pos < 65536; pos += 24) {
		memread(&c, pos, 1);
		if (c == '\0')
			break;
	}
	return pos;
}

bool mstrcmp(unsigned char* a, unsigned char* b) {
    while(*a && *a == *b)
        ++a, ++b;
    return *a == *b;
}

int findKeySpace(unsigned char key_in[MAXLEN + 1]) {
	unsigned char tmp_key[MAXLEN + 1] = { 0, };
	
	int pos;
	for (pos = 0; pos < 65536; pos += 24) {
		memread(tmp_key, pos, MAXLEN);
		if (mstrcmp(key_in, tmp_key)) {
			break;
		}
	}

	return pos;
}

int findValueSpace(unsigned char value_in[MAXLEN + 1]) {
	unsigned char tmp_value[MAXLEN + 1] = { 0, };
	
	int pos;
	for (pos = 12; pos < 65536; pos += 24) {
		memread(tmp_value, pos, MAXLEN);
		if (mstrcmp(value_in, tmp_value)) {
			break;
		}
	}

	return pos;
}

bool init(int N) {
	unsigned char c = '\0';
	int pos;
	for (pos = 0; pos < 65536; pos += 24) {
		memwrite(&c, pos, 1);
	}
	return true; // if the value of 'false' is returned, this testcase would be skipped. 
}

void put(unsigned char key_in[MAXLEN + 1], unsigned char value_in[MAXLEN + 1]) {
	int pos = getEmptySapce();
	memwrite(key_in, pos, MAXLEN);
	memwrite(value_in, pos+12, MAXLEN);
}

void del(unsigned char key_in[MAXLEN + 1]) {
	int pos = findKeySpace(key_in);
	key_in[0] = '\0';
	memwrite(key_in, pos, 1);
}

void get(unsigned char key_in[MAXLEN + 1], unsigned char value_out[MAXLEN + 1]) {
	int pos = findKeySpace(key_in);
	memread(value_out, pos + 12, MAXLEN);
	value_out[MAXLEN] = '\0';
}

void getkey(unsigned char value_in[MAXLEN + 1], unsigned char key_out[MAXLEN + 1]) {
	int pos = findValueSpace(value_in);
	memread(key_out, pos - 12, MAXLEN);
	key_out[MAXLEN] = '\0';
}