#!/usr/bin/env python

import RPi.GPIO as GPIO
import sys
sys.path.append('MFRC522-python')
from mfrc522 import SimpleMFRC522

#wav file
import pygame
import time

pygame.mixer.init()
#nfc_please.wav
#nfc_plz = pygame.mixer.Sound("nfc_please.wav")
nfc_done = pygame.mixer.Sound("nfc_done.wav.wav")

reader = SimpleMFRC522()
#nfc_plz.play()
pygame.mixer.music.load("nfc_please.wav")
pygame.mixer.music.play()
print("Hold a tag near the reader")

try:
    id, text = reader.read()
    print(id)
    #print(text)
    #nfc_done.play()
    pygame.mixer.music.load("nfc_done.wav")
    pygame.mixer.music.play()
    time.sleep(2)


finally:
    #nfc_done.play()
    #time.sleep(3)
    pygame.mixer.music.load("nfc_done.wav")
    pygame.mixer.music.play()
    GPIO.cleanup()
