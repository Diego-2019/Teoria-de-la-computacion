from bs4 import BeautifulSoup
import os

def extract_text(html_file):
    with open(html_file, 'r', encoding='utf-8') as f:
        html_content = f.read()

    soup = BeautifulSoup(html_content, 'html.parser')

    # Encuentra y elimina la etiqueta <title> y su contenido
    title_tag = soup.find('title')
    if title_tag:
        title_tag.decompose()  # Elimina la etiqueta <title> y su contenido
        
    return soup.get_text()

def create_txt(html_file):
    text = extract_text(html_file)
    with open('C:/Users/diego/Documentos/ESCOM/Programas/Teoria de la computacion/Programa 3/texto.txt', 'w', encoding='utf-8') as f:
        f.write(text)


if __name__ == '__main__':
    while True:
        name = input('Ingrese el nombre del archivo: ')
        file_dir = f'C:/Users/diego/Documentos/ESCOM/Programas/Teoria de la computacion/Programa 3/{name}.html'
        # file_dir = 'C:/Users/diego/Documentos/ESCOM/Programas/Teoria de la computacion/Programa 3/temas de genero.html'
        if os.path.exists(file_dir):
            create_txt(file_dir)
            break
        else:
            print('El archivo no existe')
            print('Intente de nuevo')
            os.system('pause')
            os.system('cls')