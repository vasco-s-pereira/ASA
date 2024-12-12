#include <iostream>
#include <vector>
#include <algorithm>

int cortarChapa(int X, int Y, std::vector<std::vector<int>> &dp)
{
    
    for (int i = 1; i <= X; i++)
    {
        for (int j = 1; j <= Y; j++)
        {   
            int max_value = 0;
            for (int k = 0; k < i/ 2 + 1; k++) {
                max_value = std::max(max_value, dp[k][j] + dp[i - k][j]);
            }

            for (int l = 0; l < j/2 + 1; l++) {
                max_value = std::max(max_value, dp[i][l] + dp[i][j - l]);
            }

            dp[i][j] = std::max(dp[i][j],max_value);
        }
    }

    return dp[X][Y];
}

int main()
{
    int X, Y;
    std::cin >> X >> Y;

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> dp(X + 1, std::vector<int>(Y + 1, 0));

    int comprimento, largura, valor;

    for (int i = 0; i < n; i++)
    {
        std::cin >> comprimento >> largura >> valor;

        if (X >= comprimento && Y >= largura)
        {
            if (valor > dp[comprimento][largura])
                dp[comprimento][largura] = valor;
        }

        if (Y >= comprimento && X >= largura && comprimento != largura)
        {
            if (valor > dp[largura][comprimento])
                dp[largura][comprimento] = valor;
        }
    }

    std::cout << cortarChapa(X, Y, dp) << std::endl;
}
