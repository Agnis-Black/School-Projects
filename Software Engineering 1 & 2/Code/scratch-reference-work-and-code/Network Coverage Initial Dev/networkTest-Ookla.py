import speedtest

speed_test = speedtest.Speedtest()

def bytes_to_mb(bytes):
  KB = 1024 # One Kilobyte is 1024 bytes
  MB = KB * 1024 # One MB is 1024 KB
  return int(bytes/MB)

download_speed = bytes_to_mb(speed_test.download())
upload_speed = bytes_to_mb(speed_test.upload())

print("Your Download speed is", download_speed, "MB")
print("Your Upload speed is", upload_speed, "MB")

# Reference: https://www.educative.io/answers/how-to-detect-internet-speed-using-python
# Notes
  # The tests take a couple seconds to gather results
  # which is kinda slow than expected but since it is
  # gathering data speeds (upload and download), it may
  # be resonable, and much more reliable than the
  # tests spelled out in 'networkTest-Navigator.js'.