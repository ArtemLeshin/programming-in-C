import pygame
import random
from pygame import mixer

pygame.init()
mixer.init()
screen = pygame.display.set_mode((800, 600))
clock = pygame.time.Clock()

# Загружаем картинки
apple = pygame.image.load("/Users/artemlesin/lab8.c/Laba9/winter_school/day3/photo/apple.png")
banana = pygame.image.load("/Users/artemlesin/lab8.c/Laba9/winter_school/day3/photo/banana.png")
basket = pygame.image.load("/Users/artemlesin/lab8.c/Laba9/winter_school/day3/photo/basket.png")
gift = pygame.image.load("/Users/artemlesin/lab8.c/Laba9/winter_school/day3/photo/gift.png")
orange = pygame.image.load("/Users/artemlesin/lab8.c/Laba9/winter_school/day3/photo/orange.png")
bomba = pygame.image.load("/Users/artemlesin/lab8.c/Laba9/winter_school/day3/photo/bomba.png")

catch_sound = mixer.Sound("/Users/artemlesin/lab8.c/Laba9/winter_school/day3/musik/2.wav")
wan_soun=mixer.Sound("/Users/artemlesin/lab8.c/Laba9/winter_school/day3/musik/1.mp3")
gift_m=mixer.Sound("/Users/artemlesin/lab8.c/Laba9/winter_school/day3/musik/gift.mp3")
death = mixer.Sound("/Users/artemlesin/lab8.c/Laba9/winter_school/day3/musik/opt.mp3")
win_m = mixer.Sound("/Users/artemlesin/lab8.c/Laba9/winter_school/day3/musik/win.mp3")
opt=mixer.Sound("/Users/artemlesin/lab8.c/Laba9/winter_school/day3/musik/gift.mp3")

spisoc_fruct = [apple, banana, orange]
fruits = []
time = 0
score = 0
hp = 3
font = pygame.font.SysFont("Arial", 30, bold=True)
speed = 90  # Начальный FPS

basket_x = 350  
game_over = False
game_win = False

running = True
while running:
    time += 1
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        # Рестарт игры
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_r and (game_over or game_win):
                fruits = []
                score = 0
                hp = 3
                game_over = False
                game_win = False
                basket_x = 350
                speed = 90
    
    # Если игра окончена 
    if game_win:
        screen.fill((100, 200, 100))
        text = font.render("GAME WIN! Нажмите R для рестарта", True, (255, 255, 255))
        screen.blit(text, (200, 250))
        pygame.display.flip()
        clock.tick(60)
        continue
    
    if game_over:
        screen.fill((200, 100, 100))
        text = font.render("GAME OVER! Нажмите R для рестарта", True, (255, 255, 255))
        screen.blit(text, (200, 250))
        pygame.display.flip()
        clock.tick(60)
        continue
    
    # Расчет скоростей на основе FPS
    move_speed = speed / 15  # 90/15=6, 120/15=8, 150/15=10
    fall_speed = speed / 40  # 90/40=2.25, 120/40=3, 150/40=3.75
    
    # Управление корзиной с динамической скоростью
    buttons = pygame.key.get_pressed()
    if (buttons[pygame.K_RIGHT] or buttons[pygame.K_d]) and basket_x < 700:
        basket_x += move_speed
    if (buttons[pygame.K_LEFT] or buttons[pygame.K_a]) and basket_x > 0:
        basket_x -= move_speed
    
    # Спавн фруктов
    if time % 90 == 0:
        fruits.append([random.randint(30, 770), -40, random.choice(spisoc_fruct)])
        
    if time % 900 == 0:
        fruits.append([random.randint(30, 770), -40, gift])
    
    if time % 800 == 0:
        fruits.append([random.randint(30, 770), -40, bomba])
    
    # Проверка условий победы/проигрыша
    if score >= 50:
        game_win = True
    
    if hp <= 0:
        game_over = True
        hp = 0
    
    # Очищаем экран
    screen.fill((255, 206, 235))
    
    # Рисуем траву
    pygame.draw.rect(screen, (0, 100, 0), (0, 570, 800, 30))
    
    # Отображаем статистику
    l = font.render(f"жизни: {hp}", True, (0, 0, 0))
    screen.blit(l, (30, 30))
    sc = font.render(f"очки: {score}", True, (0, 0, 0))
    screen.blit(sc, (30, 80))
    # Показываем текущую скорость для отладки
    spd_text = font.render(f"FPS: {int(speed)}", True, (0, 0, 0))
    screen.blit(spd_text, (30, 130))
    
    # Обновляем и отрисовываем фрукты
    fruits_to_remove = []
    
    for fruit in fruits:
        # Отрисовка
        screen.blit(fruit[2], (fruit[0], fruit[1]))
        
        # Движение вниз с динамической скоростью
        fruit[1] += fall_speed
        
        # Проверка выхода за нижнюю границу
        if fruit[1] > 560:
            fruits_to_remove.append(fruit)
            if fruit[2] != gift and fruit[2] != bomba:
                hp -= 1
                death.play()
            elif fruit[2] == gift:
                gift_m.play()
        
        # Проверка столкновения с корзиной
        hid_box = pygame.Rect(fruit[0], fruit[1], fruit[2].get_width(), fruit[2].get_height())
        hid_basket = pygame.Rect(basket_x, 550, basket.get_width(), basket.get_height())
        
        if hid_box.colliderect(hid_basket):
            fruits_to_remove.append(fruit)
            if fruit[2] == gift:
                r = random.randint(0, 1)
                if r == 0:
                    hp += 1
                    win_m.play()
                else:
                    score = max(0, score - 3)
                    opt.play()
            elif fruit[2] == bomba:
                catch_sound.play()
                hp -= 1
            else:
                wan_soun.play()
                score += 1
                if speed < 140:  # Увеличиваем максимальный FPS до 150
                    speed += 3
    
    for fruit in fruits_to_remove:
        if fruit in fruits:
            fruits.remove(fruit)
    
    # Отрисовываем корзину
    screen.blit(basket, (basket_x, 550))
    
    # Обновляем экран
    pygame.display.flip()
    clock.tick(speed)

pygame.quit()