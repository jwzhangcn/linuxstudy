#ifndef __ZGB_H__
#define	__ZGB_H__

struct acc_t {
	int x;
	int y;
	int z;
};

struct key_t {
	int flag;
	int key;
};

struct rfid_t {
	int flag;
	unsigned char data[28];
};

struct zgb_buf_t {
	int tmp;
	int hum;
	int ill;
	float adc0;
	float adc1;
	struct acc_t acc;
	struct key_t key;
	struct rfid_t rfid;
};

void *thread_zgb(void *arg);
void buf_to_zgb();

#endif
