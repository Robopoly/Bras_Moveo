#!/usr/bin/env python
# -*- coding: utf-8 -*-
import serial
import subprocess
import pygame, sys
from time import sleep


        
pygame.init()
joystick_count = pygame.joystick.get_count()

while joystick_count == 0:  # on attend que la manette soit connectée il faut réinitialiser pygame à chaque fois
    pygame.quit()
    pygame.init()
    joystick_count = pygame.joystick.get_count()
    sleep(0.1)
   
joystick = pygame.joystick.Joystick(0)
joystick.init()

ser = serial.Serial('/dev/ttyACM0', 115200) # emplacement du Serial USB
sleep(2)
liste = ['0','0','0','0','0','0','\n'] # liste contenant les indications pour chaque axe

chaine = "" # chaine des elements de la liste a envoyer a l'arduino


while True:
    
    for event in pygame.event.get():    # on parcoure les boutons etant préssés
                
        if joystick.get_axis(1) > 0.5:
            liste[3] = '2'
        elif joystick.get_axis(1) < -0.5:
            liste[3] = '1'
        else:
            liste[3] = '0'


        if joystick.get_axis(3) > 0.5:
            liste[1] = '2'
        elif joystick.get_axis(3) < -0.5:
            liste[1] = '1'
        else:
            liste[1] = '0'

        if joystick.get_button(8) and joystick.get_button(9):
            liste[2] = '0'
        elif joystick.get_button(8):
            liste[2] = '2'
        elif joystick.get_button(9):
            liste[2] = '1'
        else:
            liste[2] = '0'

        if joystick.get_button(10) and joystick.get_button(11):
            liste[0] = '0'
        elif joystick.get_button(10):
            liste[0] = '2'
        elif joystick.get_button(11):
            liste[0] = '1'
        else:
            liste[0] = '0'

        if joystick.get_button(4) and joystick.get_button(6):
            liste[4] = '0'
        elif joystick.get_button(4):
            liste[4] = '1'
        elif joystick.get_button(6):
            liste[4] = '2'
        else:
            liste[4] = '0'
            
        if joystick.get_button(14) and joystick.get_button(13):
            liste[5] = '0'
        elif joystick.get_button(14):
            liste[5] = '1'
        elif joystick.get_button(13):
            liste[5] = '2'
        else:
            liste[5] = '0'

        if joystick.get_button(0) and joystick.get_button(3):
            subprocess.Popen(['sudo','shutdown','-h','now'])
            pygame.quit()
            sys.exit()
                             
    chaine = ''.join(liste)
    ser.write(chaine)
    sleep(0.1)
