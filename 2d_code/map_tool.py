
import random

from pico2d import *

import game_framework

import main_state

backgraound_width = 1600
backgraound_height = 1800

canvas_width = 800
canvas_height = 600

map_tool = None
running = True
frame_time = 0

class Map_tool:
    PIXEL_PER_METER = (10.0 / 0.3)           # 10 pixel 30 cm
    RUN_SPEED_KMPH = 20.0                    # Km / Hour
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    TIME_PER_ACTION = 2.0
    ACTION_PER_TIME = 1.0 / TIME_PER_ACTION
    FRAMES_PER_ACTION = 8

    JUMP_HIGHT = 40                          #점프 높이
    background_image = None                 #백그라운드 이미지
    lupin_image = None                      #rupin  이미지
    trap_image = None                       #함정 이미지
    object_image = None                     #맵 오브젝트 이미지

    file = None                                #파일

    def __init__(self):

        #그림들 로드
        if(self.background_image == None):
            self.background_image = load_image('map_background.png')
        if(self.lupin_image == None):
            self.lupin_image = load_image("lupin.png")
        if(self.trap_image == None):
            self.trap_image = load_image("trap.png")
        if(self.object_image == None):
            self.object_image = load_image("map_object.png")

        #파일 로드
        if(self.file == None):
            self.file = open("Map_Data.txt", 'a')

        self.x, self.y = 0, 90
        self.draw_x, self.draw_y = None, None                              #현제 그리는 위치
        self.dir = 0                                                        #x 방향
        self.dir_y = 0                                                      #y 방향

        self.com_x = 0
        self.com_y = 0                                              #이전 그림 보정 x,y
        self.type = 1

        self.backgorund_left = 0
        self.backgorund_bottom = 0

    def __exit__(self):
        self.file.close()


    def update(self, frame_time):

        #이동
        distance = Map_tool.RUN_SPEED_PPS * frame_time
        self.x += (self.dir * distance)
        self.y += (self.dir_y * distance)

        #화면 맥시멈에 대한 체크
        if self.x > backgraound_width - (canvas_width/2):
            self.dir = 0
            self.x = backgraound_width - (canvas_width/2)
        elif self.x < 0:
            self.dir = 0
            self.x = 0


        #스크롤링에 대한 체크
            #오브젝트에 대한 체크
        if(self.x < canvas_width /2 ):
            self.draw_x = self.x
        elif( canvas_width /2 <= self.x and self.x < (backgraound_width - canvas_width)):
            self.draw_x = canvas_width/2
            self.com_x =  canvas_width/2 - self.x                               #보정 수치는 항상 -로
        elif(self.x >=  (backgraound_width - canvas_width)):
            self.draw_x = self.x - (backgraound_width - canvas_width) + canvas_width/2

        if (self.y < canvas_height/2):
            self.draw_y = self.y
        elif(self.y >=  canvas_height/2 and self.y < (backgraound_height - canvas_height)):
            self.draw_y = canvas_height/2
            self.com_y =  canvas_height/2 - self.y                              #보정 수치는 항상 -로
        elif(self.y >=  (backgraound_height - canvas_height)):
            self.draw_y = self.y - (backgraound_height - canvas_height) + canvas_height/2

            #배경에 대한 체크
        if(int(self.x) > canvas_width/2 and self.dir == 1 and int(self.x) < (backgraound_width - canvas_width)):
            self.backgorund_left +=1

        if(int(self.x) > canvas_width/2 and self.dir == -1 and int(self.x) < (backgraound_width - canvas_width)):
            self.backgorund_left -=1

        if(int(self.y) > canvas_height/2 and self.dir_y == 1 and int(self.y) < (backgraound_height - canvas_height)):
            self.backgorund_bottom +=1

        if(int(self.y) > canvas_height/2 and self.dir_y == -1 and int(self.y) < (backgraound_height - canvas_height)):
            self.backgorund_bottom -=1

    def draw(self):
        # fill here

        #background
        self.background_image.clip_draw_to_origin(int(self.backgorund_left), int(self.backgorund_bottom), int( backgraound_width - self.backgorund_left * backgraound_width / 236),int( backgraound_height - self.backgorund_bottom * backgraound_height / 270), 0, 0)

        #현제 그림
        if(self.type == 1):     #rupin
            self.lupin_image.clip_draw(100, 100, 100, 100,self.draw_x, self.draw_y)
        elif(self.type == 2):   #trap
            self.trap_image.clip_draw(100, 100, 100, 100,self.draw_x, self.draw_y)
        elif(self.type == 3):   #object 발판
            self.object_image.clip_draw(100, 0, 100, 100,self.draw_x, self.draw_y)
        elif(self.type == 4):   #object 줄
            self.object_image.clip_draw(100, 100, 100, 100,self.draw_x, self.draw_y)

        #저장된 그림들
        f = open("Map_Data.txt", 'r')

        while True:
            line = f.readline()
            if not line: break
            cur_type = int(line)

            line = f.readline()
            if not line: break
            cur_dir = int(line)

            line = f.readline()
            if not line: break
            cur_x = int(line)

            line = f.readline()
            if not line: break
            cur_y = int(line)

            if(cur_type == 1):     #rupin
                self.lupin_image.clip_draw(100, 100, 100, 100, cur_x + self.com_x, cur_y + self.com_y)
            elif(cur_type == 2):   #trap
                self.trap_image.clip_draw(100, 100, 100, 100, cur_x + self.com_x, cur_y + self.com_y)
            elif(cur_type == 3):   #object 발판
                self.object_image.clip_draw(100, 0, 100, 100, cur_x + self.com_x, cur_y + self.com_y)
            elif(cur_type == 4):   #object 줄
                self.object_image.clip_draw(100, 100, 100, 100, cur_x + self.com_x, cur_y + self.com_y)

        f.close()


    def handle_events(self, event, frame_time):

        #이동에 대한 컨트롤
        if(event.type, event.key) == (SDL_KEYDOWN, SDLK_RIGHT):
            self.dir = 1
        elif (event.type, event.key) == (SDL_KEYUP, SDLK_RIGHT):
            self.dir = 0

        if(event.type, event.key) == (SDL_KEYDOWN, SDLK_LEFT):
            self.dir = -1
        elif (event.type, event.key) == (SDL_KEYUP, SDLK_LEFT):
            self.dir = 0

        if(event.type, event.key) == (SDL_KEYDOWN, SDLK_UP):
            self.dir_y = 1
        elif(event.type, event.key) == (SDL_KEYUP, SDLK_UP):
            self.dir_y = 0

        if(event.type, event.key) == (SDL_KEYDOWN, SDLK_DOWN):
            self.dir_y = -1
        elif(event.type, event.key) == (SDL_KEYUP, SDLK_DOWN):
            self.dir_y = 0

        #type에 관한 컨트롤
        if(event.type, event.key) == (SDL_KEYDOWN, SDLK_1):
            self.type = 1
        elif(event.type, event.key) == (SDL_KEYDOWN, SDLK_2):
            self.type = 2
        elif(event.type, event.key) == (SDL_KEYUP, SDLK_3):
            self.type = 3
        elif(event.type, event.key) == (SDL_KEYUP, SDLK_4):
            self.type = 4

        #save
        elif(event.type, event.key) == (SDL_KEYUP, SDLK_s):
            self.file.write(str(int(self.type))+"\n")
            self.file.write(str(self.dir)+"\n")
            self.file.write(str(int(self.x))+"\n")
            self.file.write(str(int(self.y))+"\n")

def enter():
    # fill here
    open_canvas()
    global map_tool
    map_tool = Map_tool()


def exit():
    running = False
    global map_tool
    del(map_tool)
    close_canvas()



def pause():
    pass

def resume():
    pass


def handle_events(frame_time):
    # fill here
    events = get_events()
    for event in events:
        if(event.type, event.key) == (SDL_KEYDOWN, SDLK_ESCAPE):
            exit()
        if(event.type, event.key) == (SDL_KEYDOWN, SDLK_q):
            pass
        else:
            map_tool.handle_events(event, frame_time)

def update(frame_time):
    # fill here
    frame_time+=0.01

    map_tool.update(frame_time)

    delay(0.01)

def draw(frame_time):
    # fill here

    clear_canvas()
    map_tool.draw()
    update_canvas()

def main():
    enter()
    while running:
        handle_events(frame_time)
        update(frame_time)
        draw(frame_time)

if __name__ == '__main__':
    main()
