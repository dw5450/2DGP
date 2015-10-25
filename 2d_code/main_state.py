import random

from pico2d import *

import game_framework

backgraound_width = 1600
backgraound_height = 1800

canvas_width = 800
canvas_height = 600

boy = None
grass = None
font = None
running = True
frame_time = 0

class Background:
    def __init__(self):
        self.image = load_image('map.png')
        self.left = 0;
        self.bottom = 0;
    def set_center_object(self, boy):
        self.center_object = boy
    def draw(self):
        self.image.clip_draw_to_origin(self.left, self.bottom, int( backgraound_width - self.left * backgraound_width / 236),int( backgraound_height - self.bottom * backgraound_height / 270), 0, 0)

    def update(self, frame_time):
        if(int(boy.x) > canvas_width/2 and boy.dir == 1 and int(boy.x) < (backgraound_width - canvas_width)):
            self.left +=1

        if(int(boy.x) > canvas_width/2 and boy.dir == -1 and int(boy.x) < (backgraound_width - canvas_width)):
            self.left -=1

        if(int(boy.y) > canvas_height/2 and boy.dir_y == 1 and int(boy.y) < (backgraound_height - canvas_height)):
            self.bottom +=1

        if(int(boy.y) > canvas_height/2 and boy.dir_y == -1 and int(boy.y) < (backgraound_height - canvas_height)):
            self.bottom -=1




class Grass:
    def __init__(self):
        self.image = load_image('grass.png')

    def draw(self):
        self.image.draw(400, 30)



class Boy:
    PIXEL_PER_METER = (10.0 / 0.3)           # 10 pixel 30 cm
    RUN_SPEED_KMPH = 20.0                    # Km / Hour
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    TIME_PER_ACTION = 2.0
    ACTION_PER_TIME = 1.0 / TIME_PER_ACTION
    FRAMES_PER_ACTION = 8

    JUMP_HIGHT = 40                         #점프 높이
    image = None

    LEFT_RUN, RIGHT_RUN = 0, 1
    LEFT_STAND, RIGHT_STAND = 0, 1
    LEFT_JUMP, RIGHT_JUMP = 2, 3
    LEFT_LIE, RIGHT_LIE = 0, 1

    CAN_XMOVE = 4;              #4가능 0 불가능
    def __init__(self):
        self.x, self.y = 0, 90
        self.draw_x, self.draw_y = None, None
        self.frame = random.randint(0, 7)
        self.total_frames = 0.0
        self.dir = 0
        self.dir_y = 0;
        self.jup_max_point =  self.y + self.JUMP_HIGHT
        self.jump_dir = 0;
        self.jump_prev_state = 0;
        self.state = self.RIGHT_STAND
        if Boy.image == None:
            Boy.image = load_image('character_sprite.png')


    def update(self, frame_time):
        distance = Boy.RUN_SPEED_PPS * frame_time
        if (self.dir == 0  and (self.state == self.RIGHT_STAND or self.state == self.LEFT_STAND)) :               #멈췃을때 이미지 스프라이트가 없어서 편법 사용
             self.total_frames = 0;

        self.total_frames += Boy.FRAMES_PER_ACTION * Boy.ACTION_PER_TIME * frame_time
        self.frame = int(self.total_frames) % 4
        self.x += (self.dir * distance)
        self.y += (self.jump_dir * distance)
        self.y += (self.dir_y * distance)

        if self.x > backgraound_width - (canvas_width/2):
            self.dir = 0
            self.x = backgraound_width - (canvas_width/2)
            #self.state = self.LEFT_RUN
            #print("Change Time: %f, Total Frames: %d" % (get_time(), self.total_frames))
        elif self.x < 0:
            self.dir = 0
            self.x = 0
            #self.state = self.RIGHT_RUN
            #print("Change Time: %f, Total Frames: %d" % (get_time(), self.total_frames))

        if (self.jump_dir > 0 and self.y > self.jup_max_point):
            self.jump_dir = -1
            self.y = self.jup_max_point
        elif self.jump_dir < 0 and self.y < 90:                                                                           #추후에 충돌체크로 바꿔야함
            self.jump_dir = 0
            self.y = 90
            self.state = self.jump_prev_state

        if(self.x < canvas_width /2 and self.x < canvas_width/2):
            self.draw_x = self.x
        elif(self.x >= backgraound_width /2  and self.x < (backgraound_width - canvas_width)):
            self.draw_x = canvas_width/2
        elif(self.x >=  (backgraound_width - canvas_width)):
            self.draw_x = self.x - (backgraound_width - canvas_width) + canvas_width/2

        if (self.y < canvas_height/2):
            self.draw_y = self.y
        elif(self.y >=  canvas_height/2 and self.y < (backgraound_height - canvas_height)):
            self.draw_y = canvas_height/2
        elif(self.y >=  (backgraound_height - canvas_height)):
            self.draw_y = self.y - (backgraound_height - canvas_height) + canvas_height/2

    def draw(self):
        # fill here
         self.image.clip_draw((self.frame + self.CAN_XMOVE) * 100, self.state * 100, 100, 100,self.draw_x, self.draw_y)

    def handle_events(self, event, frame_time):
        if(event.type, event.key) == (SDL_KEYDOWN, SDLK_RIGHT):
            self.state = self.RIGHT_RUN
            self.dir = 1
        elif (event.type, event.key) == (SDL_KEYUP, SDLK_RIGHT):
            self.state = self.RIGHT_STAND
            self.dir = 0

        if(event.type, event.key) == (SDL_KEYDOWN, SDLK_LEFT):
            self.state = self.LEFT_RUN
            self.dir = -1
        elif (event.type, event.key) == (SDL_KEYUP, SDLK_LEFT):
            self.state = self.LEFT_STAND
            self.dir = 0

        elif (event.type, event.key) == (SDL_KEYDOWN, SDLK_LALT):
            if ((self.state ==  self.RIGHT_RUN or self.state ==  self.RIGHT_STAND) and self.CAN_XMOVE == 4):
                self.jump_prev_state = self.state
                self.state= self.RIGHT_JUMP
                self.jump_dir = 1
            elif ((self.state ==  self.LEFT_RUN or self.state ==  self.LEFT_STAND) and self.CAN_XMOVE == 4):
                self.jump_prev_state = self.state
                self.state = self.LEFT_JUMP
                self.jump_dir = 1

        if(event.type, event.key) == (SDL_KEYDOWN, SDLK_DOWN):
            if (self.state ==  self.RIGHT_RUN or self.state ==  self.RIGHT_STAND):
                self.state = self.RIGHT_LIE
                self.CAN_XMOVE = 0
            elif (self.state ==  self.LEFT_RUN or self.state ==  self.LEFT_STAND):
                self.state = self.LEFT_LIE
                self.CAN_XMOVE = 0

        elif(event.type, event.key) == (SDL_KEYUP, SDLK_DOWN):
            temp = self.state
            if (self.state ==  self.RIGHT_LIE):
                self.state = self.RIGHT_STAND
                self.CAN_XMOVE = 0
            elif (self.state ==  self.LEFT_LIE):
                self.state = self.LEFT_STAND
            self.CAN_XMOVE = 4

        elif(event.type, event.key) == (SDL_KEYDOWN, SDLK_q):
            self.dir_y = 1;
        elif(event.type, event.key) == (SDL_KEYUP, SDLK_q):
            self.dir_y = 0;

        elif(event.type, event.key) == (SDL_KEYDOWN, SDLK_e):
            self.dir_y = -1;
        elif(event.type, event.key) == (SDL_KEYUP, SDLK_e):
            self.dir_y = 0;



def enter():
    # fill here
    open_canvas()
    global boy, grass, map
    boy = Boy()
    grass = Grass()
    map = Background()
    map.set_center_object(boy)



def exit():
    global boy, grass
    del(boy)
    del(grass)
    del(map)
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
            close_canvas()
        else:
            boy.handle_events(event,frame_time )

def update(frame_time):
    # fill here
    frame_time+=0.01
    boy.update(frame_time)
    map.update(frame_time)
    delay(0.01);

def draw(frame_time):
    # fill here
    clear_canvas()
    map.draw()
    grass.draw()
    boy.draw()
    update_canvas()



def main():
    enter()
    while running:
        handle_events(frame_time)
        update(frame_time)
        draw(frame_time)

if __name__ == '__main__':
    main()