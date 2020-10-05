#Para ejecutar: ~$ python wiki_parser.py <path_dump> <path_parsed>

import sys
import re
SEPARADOR_VERTICE = ">"
SEPARADOR_ARISTAS = "<"


def caracter_invalido(link, titulo):
    return link != titulo and reduce(lambda pasa, y: pasa and y not in link, ["\n", SEPARADOR_VERTICE, SEPARADOR_ARISTAS], True)

def parse_page(page, output, n):
    title = page[page.index("<title>") + len("<title>") : page.index("</title>")]
    if title.isdigit():
        return # Me salteo los anios, no son interesantes
    links = filter(lambda x: caracter_invalido(x, title), map(lambda link: link[2:-2].split("|")[0], re.findall( "\[\[[^\]]*\]\]", page)))
    links = list(set(links)) #Elimino repeticiones
    if len(links) == 0:
        return
    output.write(title + SEPARADOR_VERTICE + SEPARADOR_ARISTAS.join(links) + "\n")
    

def main():
    wiki_source = open(sys.argv[1])
    article = ""
    cant = 0
    parsed_wiki = open(sys.argv[2], 'w')
    
    for line in wiki_source:
        if "<page>" in line:
            del article
            article = ""
        elif "</page>" in line:
            cant += 1
            parse_page(article, parsed_wiki, cant)
        else:
            aux = article
            article += line
            del aux
    print "Total", cant
    wiki_source.close()
    parsed_wiki.close()

if __name__ == "__main__":
    main()
