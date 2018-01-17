import time
import board
import adafruit_lis3dh
#altered to show alt readings

# Software I2C setup:
import bitbangio
i2c = bitbangio.I2C(board.SCL, board.SDA)
lis3dh = adafruit_lis3dh.LIS3DH_I2C(i2c)

# Set range of accelerometer (can be RANGE_2_G, RANGE_4_G, RANGE_8_G or RANGE_16_G).
lis3dh.range = adafruit_lis3dh.RANGE_2_G

# Loop forever printing accelerometer values
while True:
    # Read accelerometer values (in m / s ^ 2).  Returns a 3-tuple of x, y,
    # z axis values.
    x, y, z = lis3dh.acceleration
    print('x = {}G, y = {}G, z = {}G'.format(1-(x / 9.806), 1-(y / 9.806), 1-(z / 9.806))
    # Small delay to keep things responsive but give time for interrupt processing.
    time.sleep(0.1)