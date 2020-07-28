

Requisitos:

    - Motor implementado com: virabrequim, pistão, camisa, biela.
    - Camera ortográfica
    - Camera perspectiva

Extras:

    Normais por face
    Normais por vértice
    Camera em primeira pessoa, movendo pelo mouse e WASD
    Rasterização -> Rasterização de triângulos implementada com coordenadas baricentricas, com interpolação de atributos por vértice
    Backface Culling -> Faces que estão contrárias a camera não são renderizadas
    Shading:
        Iluminação por Face -> Flat Shading
        Iluminação por Vértice -> Goraud Shading
        Iluminação por Pixel -> Phong Shading e Phong Illumination Model

    Texturização -> Diffuse/Albedo mapping
    Specular Mapping -> Carregado a partir de uma textura
    Carregamento de Texturas .BMP
    Carregamento de Malhas no formato .OBJ
    Geração e Triangulação de objetos tridimensionais com normais por vértice
    Clippping para linhas
    Clipping para poligonos com interpolação de vértices, implementado baseado em: //https://dl.acm.org/doi/pdf/10.1145/965139.807398
                                                                from http://medialab.di.unipi.it/web/IUM/Waterloo/node51.html
    Pipeline Gráfico completo implementado: Model -> World -> View -> Projection -> Clip Coordinates -> NDC(Normalized Device Coordinates) -> Viewport


