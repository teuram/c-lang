#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
	
int main(int argc, char *argv[]) {

    if(argc < 2) exit(1);

	int fd;

	if((fd = open(argv[1], O_RDWR | O_NOCTTY)) == NULL) {
		exit(1);
	} 
	
	struct termios SerialPortSettings;

	tcgetattr(fd, &SerialPortSettings);

	cfsetispeed(&SerialPortSettings, B9600);
	cfsetospeed(&SerialPortSettings, B9600);

	SerialPortSettings.c_cflag &= ~PARENB;
	SerialPortSettings.c_cflag &= ~CSTOPB;
	SerialPortSettings.c_cflag &= ~CSIZE;
	SerialPortSettings.c_cflag |=  CS8;  
		
	SerialPortSettings.c_cflag &= ~CRTSCTS;
	SerialPortSettings.c_cflag |= CREAD | CLOCAL;
		
		
	SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
	SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	SerialPortSettings.c_oflag &= ~OPOST;
		
	SerialPortSettings.c_cc[VMIN] = 40;
	SerialPortSettings.c_cc[VTIME] = 10;


	if((tcsetattr(fd, TCSANOW, &SerialPortSettings)) != 0) {
	    printf("\n  ERROR ! in Setting attributes");
    } else {
		printf("\n  BaudRate = 9600 \n  StopBits = 1 \n  Parity   = none");
    }
			
	char read_buffer[64];
	int  bytes_read = 0;

	int i;

	while(1) {
		tcflush(fd, TCIFLUSH);
		bytes_read = read(fd, &read_buffer, 64);

		for(i = 0; i < bytes_read; i++) {
			printf("%c", read_buffer[i]);
        }
	}
	close(fd);

}

