import pygame
import time

pygame.mixer.init()
nfc_reco = pygame.mixer.Sound("nfc_recognized (online-audio-converter.com).wav")


nfc_reco.play()
time.sleep(3)
