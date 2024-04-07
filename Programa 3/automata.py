from graphviz import Digraph
from PIL import Image, ImageTk
import tkinter as tk

def show_dfa(img_path):
    # Crea una ventana raíz
    root = tk.Tk()
    root.attributes('-fullscreen', True)  # Abre la ventana en pantalla completa

    # Obtiene las dimensiones de la pantalla
    screen_width = root.winfo_screenwidth()
    screen_height = root.winfo_screenheight()

    # Carga y redimensiona la imagen para que se ajuste a la pantalla
    img = Image.open(img_path)
    # Usa Image.Resampling.LANCZOS si está disponible, de lo contrario, usa Image.LANCZOS
    try:
        img = img.resize((screen_width, screen_height), Image.Resampling.LANCZOS)
    except AttributeError:
        img = img.resize((screen_width, screen_height), Image.LANCZOS)
    imgTk = ImageTk.PhotoImage(img)

    # Muestra la imagen en una etiqueta (label)
    label = tk.Label(root, image=imgTk)
    label.pack(expand=True)

    # Cierra la ventana al presionar Escape
    root.bind("<Escape>", lambda e: root.destroy())

    root.mainloop()


def DFA(ruta_absoluta):
    # Crea un nuevo gráfico dirigido
    dfa = Digraph(graph_attr={'rankdir': 'LR'})

    # Añade estados al gráfico
    dfa.node('A', shape='circle')
    dfa.node('B', shape = 'circle')
    dfa.node('C', shape = 'circle')
    dfa.node('D', shape = 'circle')
    dfa.node('E', shape = 'circle')
    dfa.node('F', shape = 'circle')
    dfa.node('G', shape = 'circle')
    dfa.node('H', shape = 'circle')
    dfa.node('I', shape = 'circle')
    dfa.node('J', shape = 'circle')
    dfa.node('K', shape = 'circle')
    dfa.node('L', shape = 'circle')
    dfa.node('M', shape = 'circle')
    dfa.node('N', shape = 'circle')
    dfa.node('Ñ', shape = 'circle')
    dfa.node('O', shape = 'circle')
    dfa.node('P', shape = 'circle')
    dfa.node('Q', shape = 'circle')
    dfa.node('R', shape = 'doublecircle')
    dfa.node('S', shape = 'doublecircle')
    dfa.node('T', shape = 'doublecircle')
    dfa.node('U', shape = 'circle')
    dfa.node('V', shape = 'circle')
    dfa.node('W', shape = 'circle')
    dfa.node('X', shape = 'doublecircle')
    dfa.node('Y', shape = 'doublecircle')
    dfa.node('Z', shape = 'doublecircle')

    #! Trancisiones de A
    dfa.edge('A', 'B', label='f')
    dfa.edge('A', 'C', label='t')
    dfa.edge('A', 'D', label='v')
    dfa.edge('A', 'A', label='\u03A3-(f,t,v)')
    #! Trancisiones de B 
    dfa.edge('B', 'B', label='f')
    dfa.edge('B', 'E', label='e')
    dfa.edge('B', 'C', label='t')
    dfa.edge('B', 'D', label='v')
    dfa.edge('B', 'A', label='\u03A3-(f,e,t,v)')
    #! Trancisiones de C
    dfa.edge('C', 'B', label='f')
    dfa.edge('C', 'C', label='t')
    dfa.edge('C', 'F', label='o')
    dfa.edge('C', 'D', label='v')
    dfa.edge('C', 'A', label='\u03A3-(f,t,o,v)')
    #! Trancisiones de D
    dfa.edge('D', 'B', label='f')
    dfa.edge('D', 'G', label='i')
    dfa.edge('D', 'C', label='t')
    dfa.edge('D', 'D', label='v')
    dfa.edge('D', 'A', label='\u03A3-(f,i,t,v)')
    #! Trancisiones de E
    dfa.edge('E', 'B', label='f')
    dfa.edge('E', 'H', label='m')
    dfa.edge('E', 'C', label='t')
    dfa.edge('E', 'D', label='v')
    dfa.edge('E', 'A', label='\u03A3-(f,m,t,v)')
    #! Trancisiones de F
    dfa.edge('F', 'B', label='f')
    dfa.edge('F', 'I', label='n')
    dfa.edge('F', 'C', label='t')
    dfa.edge('F', 'J', label='r')
    dfa.edge('F', 'D', label='v')
    dfa.edge('F', 'A', label='\u03A3-(f,n,t,r,v)')
    #! Trancisiones de G
    dfa.edge('G', 'B', label='f')
    dfa.edge('G', 'K', label='e')
    dfa.edge('G', 'C', label='t')
    dfa.edge('G', 'D', label='v')
    dfa.edge('G', 'A', label='\u03A3-(f,e,t,v)')
    #! Trancisiones de H
    dfa.edge('H', 'B', label='f')
    dfa.edge('H', 'L', label='i')
    dfa.edge('H', 'C', label='t')
    dfa.edge('H', 'D', label='v')
    dfa.edge('H', 'A', label='\u03A3-(f,i,t,v)')
    #! Trancisiones de I
    dfa.edge('I', 'B', label='f')
    dfa.edge('I', 'V', label='t')
    dfa.edge('I', 'D', label='v')
    dfa.edge('I', 'A', label='\u03A3-(f,t,v)')
    #! Trancisiones de J
    dfa.edge('J', 'B', label='f')
    dfa.edge('J', 'W', label='t')
    dfa.edge('J', 'D', label='v')
    dfa.edge('J', 'A', label='\u03A3-(f,t,v)')
    #! Trancisiones de K
    dfa.edge('K', 'B', label='f')
    dfa.edge('K', 'C', label='t')
    dfa.edge('K', 'D', label='v')
    dfa.edge('K', 'N', label='j')
    dfa.edge('K', 'A', label='\u03A3-(f,t,v,j)')
    #! Trancisiones de L
    dfa.edge('L', 'B', label='f')
    dfa.edge('L', 'M', label='n')
    dfa.edge('L', 'C', label='t')
    dfa.edge('L', 'D', label='v')
    dfa.edge('L', 'A', label='\u03A3-(f,n,t,v)')
    #! Trancisiones de M
    dfa.edge('M', 'B', label='f')
    dfa.edge('M', 'Ñ', label='i')
    dfa.edge('M', 'O', label='a')
    dfa.edge('M', 'C', label='t')
    dfa.edge('M', 'D', label='v')
    dfa.edge('M', 'A', label='\u03A3-(f,i,a,t,v)')
    #! Trancisiones de N
    dfa.edge('N', 'B', label='f')
    dfa.edge('N', 'T', label='a')
    dfa.edge('N', 'C', label='t')
    dfa.edge('N', 'D', label='v')
    dfa.edge('N', 'A', label='\u03A3-(f,a,t,v)')
    #! Trancisiones de Ñ
    dfa.edge('Ñ', 'B', label='f')
    dfa.edge('Ñ', 'P', label='s')
    dfa.edge('Ñ', 'C', label='t')
    dfa.edge('Ñ', 'D', label='v')
    dfa.edge('Ñ', 'A', label='\u03A3-(f,s,t,v)')
    #! Trancisiones de O
    dfa.edge('O', 'B', label='f')
    dfa.edge('O', 'R', label='l')
    dfa.edge('O', 'Q', label='z')
    dfa.edge('O', 'C', label='t')
    dfa.edge('O', 'D', label='v')
    dfa.edge('O', 'A', label='\u03A3-(f,l,z,t,v)')
    #! Trancisiones de P
    dfa.edge('P', 'B', label='f')
    dfa.edge('P', 'U', label='t')
    dfa.edge('P', 'D', label='v')
    dfa.edge('P', 'A', label='\u03A3-(f,t,v)')
    #! Trancisiones de Q
    dfa.edge('Q', 'B', label='f')
    dfa.edge('Q', 'S', label='i')
    dfa.edge('Q', 'C', label='t')
    dfa.edge('Q', 'D', label='v')
    dfa.edge('Q', 'A', label='\u03A3-(f,i,t,v)')
    #! Trancisiones de R
    dfa.edge('R', 'B', label='f')
    dfa.edge('R', 'C', label='t')
    dfa.edge('R', 'D', label='v')
    dfa.edge('R', 'A', label='\u03A3-(f,t,v)')
    #! Trancisiones de S
    dfa.edge('S', 'B', label='f')
    dfa.edge('S', 'C', label='t')
    dfa.edge('S', 'D', label='v')
    dfa.edge('S', 'A', label='\u03A3-(f,t,v)')
    #! Trancisiones de T
    dfa.edge('T', 'B', label='f')
    dfa.edge('T', 'C', label='t')
    dfa.edge('T', 'D', label='v')
    dfa.edge('T', 'A', label='\u03A3-(f,t,v)')
    #! Trancisiones de U
    dfa.edge('U', 'B', label='f')
    dfa.edge('U', 'X', label='a')
    dfa.edge('U', 'C', label='t')
    dfa.edge('U', 'F', label='o')
    dfa.edge('U', 'D', label='v')
    dfa.edge('U', 'A', label='\u03A3-(f,a,t,o,v)')
    #! Trancisiones de V
    dfa.edge('V', 'B', label='f')
    dfa.edge('V', 'Y', label='a')
    dfa.edge('V', 'C', label='t')
    dfa.edge('V', 'F', label='o')
    dfa.edge('V', 'D', label='v')
    dfa.edge('V', 'A', label='\u03A3-(f,a,t,o,v)')
    #! Trancisiones de W
    dfa.edge('W', 'B', label='f')
    dfa.edge('W', 'Z', label='a')
    dfa.edge('W', 'C', label='t')
    dfa.edge('W', 'F', label='o')
    dfa.edge('W', 'D', label='v')
    dfa.edge('W', 'A', label='\u03A3-(f,a,t,o,v)')
    #! Trancisiones de X
    dfa.edge('X', 'B', label='f')
    dfa.edge('X', 'C', label='t')
    dfa.edge('X', 'D', label='v')
    dfa.edge('X', 'A', label='\u03A3-(f,t,v)')
    #! Trancisiones de Y
    dfa.edge('Y', 'B', label='f')
    dfa.edge('Y', 'C', label='t')
    dfa.edge('Y', 'D', label='v')
    dfa.edge('Y', 'A', label='\u03A3-(f,t,v)')
    #! Trancisiones de Z
    dfa.edge('Z', 'B', label='f')
    dfa.edge('Z', 'C', label='t')
    dfa.edge('Z', 'D', label='v')
    dfa.edge('Z', 'A', label='\u03A3-(f,t,v)')

    # Visualiza el gráfico
    dfa.render(ruta_absoluta, format='png', cleanup=True)


if __name__ == '__main__':
    ruta_absoluta = 'C:/Users/diego/Documentos/ESCOM/Programas/Teoria de la computacion/Programa 3/automata'
    DFA(ruta_absoluta)
    show_dfa(ruta_absoluta + '.png')
