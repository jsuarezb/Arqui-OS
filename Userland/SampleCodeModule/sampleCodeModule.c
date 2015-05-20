char * v = (char*)0xB8000 + 79 * 2;

extern char bss;
extern char endOfBinary;

int main() {
	*v = 'X';
	// TODO: set 0 from bss to endOfBinary
	return 0xDEADBEEF;
}
