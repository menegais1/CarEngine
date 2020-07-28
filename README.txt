
Instruções;

    Movimento da Câmera:
        W - Mover para direção que a camera está vendo
        S - Mover ao lado contrário da direção de visão
        D - Mover para direita
        A - Mover para esquerda
        Q - Mover camera para cima
        E - Mover camera para baixo
        Segurar botão esquerdo e mover mouse: Modifica visão da camera

    N - Ativar normais por vértice
    F - Ativar normais por face
    M - Ativar rasterização
        J - Rasterização com Flat Shading
        K - Rasterização com Goraud Shading
        L - Rasterização com Phong Shading
    O - Camera ortografica
    P - Camera perspectiva
    Z - Ativa Biela
    X - Ativa Pistão
    C - Ativa Camisa
    V - Ativa Virabrequim
    1, 2, 3 - Ativa a quantidade de pistões conectados ao virabrequim


Observações:
    - Para manter o desempenho aceitavel, modelos de baixa qualidade foram usados, porém no projeto há modelos com mais vértices e triangulos.
    - O programa demora a iniciar devido ao carregamento dos .obj e das texturas em .BPM, que são de 2K
    - Como existe controle de FPS, em FPS baixo com RPM alto, o virabrequim pode parecer "parado" ou estar se movendo para trás, isso ocorre devido a cada rotação que ele precisa fazer ser maior ou muito próxima de 360 por frame, gerando a ilusão.


Requisitos Implementados:

    - Motor implementado com: virabrequim, pistão, camisa, biela.
    - Camera ortográfica
    - Camera perspectiva
    - Controle de RPM entre 1 a 10000, com passos de 500 a 500

Extras:

   1 - Normais por face
   2 - Normais por vértice
   3 - Camera em primeira pessoa, movendo pelo mouse e WASD
   4 - Rasterização -> Rasterização de triângulos implementada com coordenadas baricentricas, com interpolação de atributos por vértice (fonte: https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage)
   5 - Backface Culling -> Faces que estão contrárias a camera não são renderizadas (fonte: https://en.wikipedia.org/wiki/Back-face_culling)
        5.1 -> Ganho de aproximadamente 7 a 8 FPS (teste empirico)
   6 - Shading:
       6.1 - Iluminação por Face -> Flat Shading (fonte: https://cglearn.codelight.eu/pub/computer-graphics/shading-and-lighting)
       6.2 - Iluminação por Vértice -> Goraud Shading (fonte: https://en.wikipedia.org/wiki/Gouraud_shading)
       6.3 - Iluminação por Pixel -> Phong Shading e Phong Illumination Model (fonte: https://en.wikipedia.org/wiki/Phong_reflection_model)
   7 - Texturização -> Diffuse/Albedo mapping (fonte: https://learnopengl.com/Lighting/Lighting-maps)
   8 - Specular Mapping -> Carregado a partir de uma textura (fonte: https://learnopengl.com/Lighting/Lighting-maps)
   9 - Carregamento de Texturas .BMP
  10 - Carregamento de Malhas no formato .OBJ
  11 - Geração e Triangulação de objetos tridimensionais com normais por vértice
  12 - Clippping para linhas (fonte: //https://dl.acm.org/doi/pdf/10.1145/965139.807398)
  13 - Clipping para poligonos com interpolação de vértices (fonte: //https://dl.acm.org/doi/pdf/10.1145/965139.807398
                                                                from http://medialab.di.unipi.it/web/IUM/Waterloo/node51.html)
  14 - Pipeline Gráfico completo implementado: Model -> World -> View -> Projection -> Clip Coordinates / Backface Culling-> NDC(Normalized Device Coordinates) -> Viewport -> Rasterization (fonte: https://en.wikipedia.org/wiki/Graphics_pipeline)
  15 - Mais de 1 Pistão (3)
  16 - Redimensionamento da tela com correção de aspect ratio
  17 - Visible surface definition -> Algortimo de Z-BUFFER ( fonte: https://pt.wikipedia.org/wiki/Z-buffer)
