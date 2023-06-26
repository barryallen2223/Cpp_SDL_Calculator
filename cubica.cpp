#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <math.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int AXIS_COLOR_R = 0;
const int AXIS_COLOR_G = 255;
const int AXIS_COLOR_B = 0;
const int AXIS_THICKNESS = 2;
const std::string FONT_PATH = "MathematicalBold.ttf";
const int FONT_SIZE = 20;

int main()
{
    double m = 0, a = 0, b = 0, c = 0, d = 0;
    printf("y = ax^3 + bx^2 + cx + d\n--------------------------\n");
    printf("a: ");
    scanf("%lf", &a);
    printf("b: ");
    scanf("%lf", &b);
    printf("c: ");
    scanf("%lf", &c);
    printf("d: ");
    scanf("%lf", &d);

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("Graph Calculator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Set color for axes
    SDL_SetRenderDrawColor(renderer, AXIS_COLOR_R, AXIS_COLOR_G, AXIS_COLOR_B, SDL_ALPHA_OPAQUE);

    // Draw X-axis
    SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
    // Draw X-axis - sections
    for (int section = (WINDOW_WIDTH / 10); section < WINDOW_WIDTH; section += (WINDOW_WIDTH / 10))
    {
        SDL_RenderDrawLine(renderer, section, ((WINDOW_HEIGHT / 2) - 10), section, ((WINDOW_HEIGHT / 2) + 10));
    }
    // Draw Y-axis
    SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
    // Draw Y-axis - sections
    for (int section = (WINDOW_HEIGHT / 10); section < WINDOW_HEIGHT; section += (WINDOW_HEIGHT / 10))
    {
        SDL_RenderDrawLine(renderer, ((WINDOW_WIDTH / 2) - 10), section, ((WINDOW_WIDTH / 2) + 10), section);
    }
    // Set color for the quadratic function
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

    // Plot the quadratic function
    a /= 10;
    b /= 10;
    c *= (WINDOW_HEIGHT / 10);
    for (int x = -WINDOW_WIDTH / 2; x <= WINDOW_WIDTH / 2; x++)
    {
        int startX = x;
        int startY = (a * pow((double)x, (double)3)) + (b * pow((double)x, (double)2)) + (c * x) + d;
        int endX = x + 1;
        int endY = (a * pow((double)endX, (double)3)) + (b * pow((double)endX, (double)2))  + (c * endX) + d;

        // Adjust coordinates to match SDL's coordinate system and start from the origin
        int originX = WINDOW_WIDTH / 2;
        int originY = WINDOW_HEIGHT / 2;
        startX += originX;
        startY = originY - startY;
        endX += originX;
        endY = originY - endY;
        //printf("a: %lf, b: %lf, c: %lf, x1: %d, y1: %d, x2: %d, y2: %d\n", a, b, c, startX, startY, endX, endY);
        SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
    }

    // Load font
    TTF_Font *font = TTF_OpenFont(FONT_PATH.c_str(), FONT_SIZE);
    if (!font)
    {
        // Error handling if font loading fails
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Set color for labels
    SDL_Color textColor = {AXIS_COLOR_R, AXIS_COLOR_G, AXIS_COLOR_B, SDL_ALPHA_OPAQUE};

    // Render X-axis label
    std::string xAxisLabel = "X";
    SDL_Surface *xLabelSurface = TTF_RenderText_Solid(font, xAxisLabel.c_str(), textColor);
    SDL_Texture *xLabelTexture = SDL_CreateTextureFromSurface(renderer, xLabelSurface);
    int xLabelWidth = xLabelSurface->w;
    int xLabelHeight = xLabelSurface->h;
    SDL_Rect xLabelRect = {WINDOW_WIDTH - xLabelWidth - 5, WINDOW_HEIGHT / 2 - xLabelHeight - 5, xLabelWidth, xLabelHeight};
    SDL_RenderCopy(renderer, xLabelTexture, nullptr, &xLabelRect);

    // Render Y-axis label
    std::string yAxisLabel = "Y";
    SDL_Surface *yLabelSurface = TTF_RenderText_Solid(font, yAxisLabel.c_str(), textColor);
    SDL_Texture *yLabelTexture = SDL_CreateTextureFromSurface(renderer, yLabelSurface);
    int yLabelWidth = yLabelSurface->w;
    int yLabelHeight = yLabelSurface->h;
    SDL_Rect yLabelRect = {WINDOW_WIDTH / 2 + 5, 5, yLabelWidth, yLabelHeight};
    SDL_RenderCopy(renderer, yLabelTexture, nullptr, &yLabelRect);

    // Clean up font and surface
    TTF_CloseFont(font);
    SDL_FreeSurface(xLabelSurface);
    SDL_FreeSurface(yLabelSurface);
    SDL_DestroyTexture(xLabelTexture);
    SDL_DestroyTexture(yLabelTexture);

    SDL_RenderPresent(renderer);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}