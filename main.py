import cv2
import math
import time
import mod

def rotate(angle:float):
    templateImg = cv2.imread("./images/temp_2.png")
    targetImg = cv2.imread("./images/group_young_world.png")

    hight = templateImg.shape[0]
    width = templateImg.shape[1]
    center = (int(width / 2), int(hight / 2))

    scale = 1.0

		rad = math.radians(angle)

    newWidth = int(width * abs(math.cos(rad)) + hight * abs(math.sin(rad)))
    newHight = int(width * abs(math.sin(rad)) + hight * abs(math.cos(rad)))

    transition = cv2.getRotationMatrix2D(center, angle, scale)
    resultImg = cv2.warpAffine(templateImg, transition, (newWidth, newHight))

    search = cv2.matchTemplate(targetImg, resultImg, cv2.TM_CCOEFF_NORMED)

    return search

def main():
    startTime =  time.time()

    maxV_store = 0;
    for i in range(1, 360):
        _, maxV, _, maxL = cv2.minMaxLoc(rotate(i))

        if maxV > maxV_store:
            maxL_store = maxL

    endTime = time.time() - startTime
    print("python")
    print("angle:\t{}".format(i))
    print("x:\t{}".format(maxL_store[0]))
    print("y:\t{}".format(maxL_store[1]))
    print("time[s]:{}".format(endTime))

    print("\n")

    print("c++ non threads")
    startTime = time.time()
    mod.mod_1thd()
    endTime = time.time() - startTime
    print("time[s]:{}".format(endTime))

    print("\n")

    print("c++ 4 threads")
    startTime = time.time()
    mod.mod_4thd()
    endTime = time.time() - startTime
    print("time[s]:{}".format(endTime))


if __name__ == '__main__':
    main()
