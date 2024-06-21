import pygame
import sys
import os

# Definicion de colores
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)

# Configuracion de Pygame
pygame.init()
size = (800, 300)
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Maquina de Turing")
clock = pygame.time.Clock()
font = pygame.font.Font(None, 36)

# Definicion de la clase Maquina de Turing
class TuringMachine:
    def __init__(self, tape, initial_state, transitions):
        self.tape = list(tape)
        self.tape.append('B')  # Simbolo blanco al final de la cinta
        self.head_position = 0
        self.state = initial_state
        self.transitions = transitions

    def step(self):
        if self.head_position < 0 or self.head_position >= len(self.tape):
            return False
        current_symbol = self.tape[self.head_position]
        if (self.state, current_symbol) not in self.transitions:
            return False
        new_state, new_symbol, direction = self.transitions[(self.state, current_symbol)]
        self.tape[self.head_position] = new_symbol
        self.state = new_state
        if direction == 'R':
            self.head_position += 1
        elif direction == 'L':
            self.head_position -= 1
        return True

# Leemos tape y result_text del archivo
path = 'C:/Users/diego/Documentos/ESCOM/Programas/Teoria de la computacion/Segundo bloque/Programa 7/animationTM.txt'
with open(path, 'r') as file:
    lines = file.readlines()
    tape = lines[0].strip()
    result_text = lines[1].strip()

# Eliminamos el archivo de animacion
os.remove(path)

initial_state = 'A'
# Definicion de las transiciones de la maquina de Turing
transitions = {
    ('A', '0'): ('B', 'X', 'R'),
    ('A', 'Y'): ('D', 'Y', 'R'),
    ('B', '0'): ('B', '0', 'R'),
    ('B', '1'): ('C', 'Y', 'L'),
    ('B', 'Y'): ('B', 'Y', 'R'),
    ('C', '0'): ('C', '0', 'L'),
    ('C', 'X'): ('A', 'X', 'R'),
    ('C', 'Y'): ('C', 'Y', 'L'),
    ('D', 'Y'): ('D', 'Y', 'R'),
    ('D', 'B'): ('E', 'B', 'R')
}

machine = TuringMachine(tape, initial_state, transitions)

# Funcion para dibujar la cinta y el cabezal
def draw_turing_machine(machine):
    screen.fill(WHITE)

    tape_length = len(machine.tape)
    cell_width = 40
    start_x = (size[0] - tape_length * cell_width) // 2
    
    for i, symbol in enumerate(machine.tape):
        x = start_x + i * cell_width
        y = 50
        rect = pygame.Rect(x, y, cell_width, cell_width)
        pygame.draw.rect(screen, BLACK, rect, 2)
        text = font.render(symbol, True, BLACK)
        screen.blit(text, (x + 10, y + 5))

    head_x = start_x + machine.head_position * cell_width
    pygame.draw.polygon(screen, BLUE, [(head_x + 10, 115), (head_x + 30, 115), (head_x + 20, 95)])

    state_text = font.render(f"Estado: {machine.state}", True, BLACK)
    screen.blit(state_text, (340, 180))

    pygame.display.flip()

# Bucle principal de Pygame
running = True
paused = False
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    if not paused:
        draw_turing_machine(machine)
        pygame.time.delay(1000)  # Esperar 1 segundo entre pasos

        if not machine.step():
            paused = True  # Pausar la animacion si no hay mas pasos

    if paused:
        # Mostrar el resultado final
        screen.fill(WHITE)
        text = font.render(result_text, True, BLACK)
        screen.blit(text, (size[0] // 2 - 130, size[1] // 2 - 50))
        pygame.display.flip()
        pygame.time.wait(3000)
        running = False

    clock.tick(60)

pygame.quit()
sys.exit()
