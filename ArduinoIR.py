#!python3
#encoding=utf-8
from __future__ import print_function, division, absolute_import

def cmd(command):
    os.system(command)

class Tecla:
    def __init__(self, name, codes, vk = None):
        self.name = name
        self.codes = codes
        self.vk = vk

    def match(self, code):
        for c in self.codes:
            if c[0:7] == code[0:7]:
                return True

    def do(self):
        # teclas especiais
        if self.name == 'POWER':
            print('d')
            sys.exit(0)
        else:
            # apenas executo a partir do nircmd
            cmd('nircmd sendkeypress '+(self.name if self.vk is None else self.vk))

    def __str__(self):
        return 'Tecla(%s)' % self.name

teclas = [
    Tecla(
        'MUTE',
        ['48820DF'],
        '0xAD'
    ),

    Tecla(
        'POWER',
        ['48800FF']
    ),

    Tecla(
        'up',
        ['48848B7']
    ),

    Tecla(
        'right',
        ['4886897']
    ),

    Tecla(
        'down',
        ['488C837']
    ),

    Tecla(
        'left',
        ['48828D7']
    ),
]


def findTecla(code):
    for t in teclas:
        if t.match(code):
            return t
    return None

import sys
DEBUG = sys.flags.debug or True
def debug(*args):
    '''funciona como print, mas só é executada se sys.flags.debug == 1'''
    if not DEBUG:
        return ;
    print(*args)


import serial
import time
import os

con = serial.Serial('COM3', 9600)

code = b''
lastCode = ''
lastTime = time.time()
while True:
    # lê um char
    ch = con.read()
    # lê outro char
    code += ch

    if ch == b'\n':
        code = code.decode('utf-8').replace('\r\n', '')
        if code == 'FFFFFFFF':
            code = lastCode
        # o último código é ele
        lastCode = code

        now = time.time()
        timeSpent = now - lastTime

        if timeSpent >= 0.1:
            tecla = findTecla(code)
            if tecla is not None:
                tecla.do()
            else:
                debug("codigo não reconhecido: %s" % code)

        # para recomeçar o loop
        lastTime = now
        code = b''
