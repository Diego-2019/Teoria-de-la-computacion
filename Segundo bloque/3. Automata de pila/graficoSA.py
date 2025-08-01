import pygame
import sys
import math
import os

# Inicializar pygame
pygame.init()

# Configuracion de la pantalla
width, height = 1535, 790
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Automata de Pila")

# Colores
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)

# Fuente
font = pygame.font.Font(None, 36)

# Definicion del automata de pila
states = ['q', 'p', 'f']
transitions = {
    ('q', '0', 'Z'): ('q', 'XZ'),
    ('q', '0', 'X'): ('q', 'XX'),
    ('q', '1', 'X'): ('p', 'e'),
    ('p', '1', 'X'): ('p', 'e'),
    ('p', 'e', 'Z'): ('f', 'Z')
}
start_state = 'q'
accept_states = ['f']

# Leer input_string y result_text del archivo
file_path = '../3. Automata de pila/animation.txt'
with open(file_path, 'r') as file:
    lines = file.readlines()
    input_string = lines[0].strip()  # Primera linea para input_string
    result_text = lines[1].strip()   # Segunda linea para result_text

# Borrar el archivo de animacion
os.remove(file_path)

# Inicializar el automata
current_state = start_state
stack = ['Z']
input_pointer = 0

# Funcion para dibujar una flecha
def draw_arrow(start, end, color=BLACK, arrow_size=10, arrow_angle=30):
    pygame.draw.line(screen, color, start, end, 2)
    angle = math.atan2(end[1] - start[1], end[0] - start[0])
    left_arrow = (end[0] - arrow_size * math.cos(angle - math.radians(arrow_angle)),
                  end[1] - arrow_size * math.sin(angle - math.radians(arrow_angle)))
    right_arrow = (end[0] - arrow_size * math.cos(angle + math.radians(arrow_angle)),
                   end[1] - arrow_size * math.sin(angle + math.radians(arrow_angle)))
    pygame.draw.polygon(screen, color, [end, left_arrow, right_arrow])

# Funcion para dibujar el automata
def draw_automaton():
    screen.fill(WHITE)

    # Posicion del estado actual
    state_position = {
        'q': (width // 2 - 30, height // 2 - 30),
        'p': (width // 2 - 30, height // 2 - 30),
        'f': (width // 2 - 30, height // 2 - 30)
    }

    pos = state_position[current_state]
    pygame.draw.rect(screen, GREEN, (*pos, 60, 60), 0)
    pygame.draw.rect(screen, BLACK, (*pos, 60, 60), 2)
    text = font.render(current_state, True, BLUE)
    screen.blit(text, (pos[0] + 20, pos[1] + 15))

    # Dibujar cadena de entrada
    input_text = font.render(f'Entrada: {input_string[input_pointer:]}', True, BLACK)
    screen.blit(input_text, (pos[0] - 100, pos[1] - 170))

    # Dibujar pila
    stack_text = font.render(f'Pila: {" ".join(stack)}', True, BLACK)
    screen.blit(stack_text, (pos[0] - 50, pos[1] + 180))

    # Dibujar flecha hacia la cadena de entrada
    draw_arrow((pos[0] + 30, pos[1]), (pos[0] + 30, pos[1] - 140))

    # Dibujar flecha hacia la pila
    draw_arrow((pos[0] + 30, pos[1] + 60), (pos[0] + 30, pos[1] + 170))

    pygame.display.flip()

# Funcion para procesar la cadena de entrada
def process_input():
    global current_state, stack, input_pointer
    if input_pointer < len(input_string):
        symbol = input_string[input_pointer]
        stack_top = stack.pop() if stack else ''
        key = (current_state, symbol, stack_top)
        if key in transitions:
            next_state, stack_action = transitions[key]
            current_state = next_state
            for char in reversed(stack_action):
                if char != 'e':  # Asegurarse de no apilar 'e'
                    stack.append(char)
            input_pointer += 1
            return True
    elif (current_state, 'e', stack[-1]) in transitions:
        stack_top = stack.pop()
        next_state, stack_action = transitions[(current_state, 'e', stack_top)]
        current_state = next_state
        for char in reversed(stack_action):
            if char != 'e':  # Asegurarse de no apilar 'e'
                stack.append(char)
        return True
    return False

# Bucle principal
running = True
clock = pygame.time.Clock()

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    draw_automaton()

    if not process_input():
        pygame.time.wait(1000)
        # Mostrar el resultado final
        screen.fill(WHITE)
        text = font.render(result_text, True, BLACK)
        screen.blit(text, (width // 2 - text.get_width() // 2, height // 2 - text.get_height() // 2))
        pygame.display.flip()
        pygame.time.wait(3000)
        running = False

    clock.tick(1)  # Controlar la velocidad de la animacion

pygame.time.wait(1000)

# Cerrar pygame
pygame.quit()

# Salir del programa
sys.exit()
