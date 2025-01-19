const HtmlWebpackPlugin = require('html-webpack-plugin');
const path = require('path');
const { BundleAnalyzerPlugin } = require('webpack-bundle-analyzer');
const CopyWebpackPlugin = require('copy-webpack-plugin'); // Adicionado aqui

module.exports = {
  entry: './src/index.js',
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'bundle.js',
  },
  module: {
    rules: [
      {
        test: /\.svg$/,
        use: [
          {
            loader: '@svgr/webpack',
          },
          {
            loader: 'file-loader',
            options: {
              name: 'assets/icons/[name].[hash].[ext]',
            },
          },
        ],
      },
      {
        test: /\.(js|jsx)$/,
        exclude: /node_modules/,
        use: 'babel-loader',
      },
      {
        test: /\.scss$/, // Aplica a regra a arquivos .scss
        use: [
          { loader: 'style-loader' }, // Insere o CSS no DOM
          { loader: 'css-loader' },   // Processa os arquivos CSS
          { loader: 'sass-loader',
            options: {
              implementation: require('sass'),
              sassOptions: {
                includePaths: [path.resolve(__dirname, 'src')],
              },
            },

           },  // Converte SCSS para CSS
        ],
      },
      {
        test: /\.css$/, // Para arquivos CSS
        use: [
          'style-loader', // Insere o CSS no DOM
          'css-loader',   // Processa o CSS
        ],
      },
    ],
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: path.resolve(__dirname, 'dist', 'index.html'), // Caminho correto para o arquivo HTML
      inject: false,
    }),
    new CopyWebpackPlugin({
      patterns: [
        { from: './src/style', to: '' }, // Exemplo: copia a pasta `assets` para `dist/assets`
      ],
    }),
    // new BundleAnalyzerPlugin(),

  ],
  devServer: {
    static: path.resolve(__dirname, 'dist'),
    port: 3000,
    hot: true,        // Habilitar Hot Module Replacement (HMR)
    open: true,
  },
  resolve: {
    extensions: ['.js', '.jsx', '.scss', '.css'],
    alias: {
      '@emotion/react': require.resolve('@emotion/react'),
    },
  },
  optimization: {
    usedExports: true, // Remove código não utilizado
    minimize: true     // Minifica o bundle
  }

};
