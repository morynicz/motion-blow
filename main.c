#include <wiringPiI2C.h>
#include <unistd.h>
#include <stdio.h>

#define CHANNEL 0
#define SPEED   1000000

#define MPU9255_I2C_ADDRESS 0x68

#define MPU9255_ACCEL_XOUT   0x3B
#define MPU9255_ACCEL_XOUT_L 0x3C
#define MPU9255_ACCEL_YOUT   0x3D
#define MPU9255_ACCEL_YOUT_L 0x3E
#define MPU9255_ACCEL_ZOUT   0x3F
#define MPU9255_ACCEL_ZOUT_L 0x40

#define MPU9255_GYRO_XOUT    0x43
#define MPU9255_GYRO_XOUT_L  0x44
#define MPU9255_GYRO_YOUT    0x45
#define MPU9255_GYRO_YOUT_L  0x46
#define MPU9255_GYRO_ZOUT    0x47
#define MPU9255_GYRO_ZOUT_L  0x48


#define MPU9255_ACCEL_CONFIG 0x1C<<2
#define MPU9255_ACCEL_FS_2G  0x00<<2
#define MPU9255_ACCEL_FS_4G  0x01<<2
#define MPU9255_ACCEL_FS_8G  0x10<<2
#define MPU9255_ACCEL_FS_16G 0x11<<2

#define MPU9255_PWR_MGMT     0x6B

#define MPU9255_WHOAMI     0x75

struct Point3d {
  int x;
  int y;
  int z;
};


int assemble16(int l, int h) {
  return (h<<8)|(l & 0xff);
}



int mpu9255Read3dRegisters(int fd, int xLAddr, int xHAddr,
			   int yLAddr, int yHAddr, int zLAddr,
			   int zHAddr, struct Point3d *point)
{
  int xl, xh, yl, yh, zl, zh;

  /*
    x = wiringPiI2CReadReg16(fd, ACCEL_XOUT);
    y = wiringPiI2CReadReg16(fd, ACCEL_YOUT);
    z = wiringPiI2CReadReg16(fd, ACCEL_ZOUT);
  */
    
  xl = wiringPiI2CReadReg8(fd, xLAddr);
  xh = wiringPiI2CReadReg8(fd, xHAddr);
  yl = wiringPiI2CReadReg8(fd, yLAddr);
  yh = wiringPiI2CReadReg8(fd, yHAddr);
  zl = wiringPiI2CReadReg8(fd, zLAddr);
  zh = wiringPiI2CReadReg8(fd, zHAddr);

  point->x = assemble16(xl, xh);
  point->y = assemble16(yl, yh);
  point->z = assemble16(yl, yh);
  
}

int mpu9255ReadAccel(int fd, struct Point3d *point) {
    int xl, xh, yl, yh, zl, zh;

    mpu9255Read3dRegisters(fd, MPU9255_ACCEL_XOUT_L, 
			   MPU9255_ACCEL_XOUT, MPU9255_ACCEL_YOUT_L, 
			   MPU9255_ACCEL_YOUT, MPU9255_ACCEL_ZOUT_L, 
			   MPU9255_ACCEL_ZOUT, point); 
}

int main(int argc, char* argv) {
  int fd, result;

  fd = wiringPiI2CSetup(MPU9255_I2C_ADDRESS);

  int w = wiringPiI2CReadReg8(fd, MPU9255_WHOAMI);

  wiringPiI2CWriteReg16(fd, MPU9255_PWR_MGMT, 1 <<15);
  sleep(1);
  wiringPiI2CWriteReg16(fd, MPU9255_ACCEL_CONFIG,
			MPU9255_ACCEL_FS_16G);
  
  printf("mot = [\n");
  for(int i=0; i<1000; ++i) {
    int x ,y, z;
    struct Point3d point;
    mpu9255ReadAccel(fd, &point);
    printf("%d %d %d %d\n",i, point.x, point.y, point.z);
    usleep(1);
  }
  printf("]\n");
  close(fd);
  return 0;
}

