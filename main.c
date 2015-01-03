int main() {
	outb(0x3D4h, 'A');
	outb(0x3D4h + 1 , 7);
	for(;;){};
}
