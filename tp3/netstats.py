#!/usr/bin/python3
import sys
from utils import parse_tsv, ParametrosFaltantes
from net import Net


def main():
  if len(sys.argv) < 2:
      raise ParametrosFaltantes
  else:
      datos = parse_tsv(sys.argv[1])
      _net = Net(datos)
      while True:
        entrada = input()
        if entrada == "": 
          break
        _net.procesar_comando(entrada)


if __name__ == '__main__':
  try:
    main()
  except KeyboardInterrupt:
    exit()
  except EOFError:
    pass