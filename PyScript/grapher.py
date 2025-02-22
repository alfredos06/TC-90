from turtle import *

dragVarv = 1000

accTime = 1000

currentAcc = 0

rpm = int(input('RPM;'))

pwrTarget = rpm / 1000

if rpm >= dragVarv:

    while currentAcc < accTime:
        currentAcc += 1

        k = pwrTarget / accTime

        pwr = k * currentAcc

        goto(pwr, currentAcc)




