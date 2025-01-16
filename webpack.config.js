const HtmlWebpackPlugin = require('html-webpack-plugin');
const path = require('path');
const { BundleAnalyzerPlugin } = require('webpack-bundle-analyzer');


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
        use: ['@svgr/webpack'],
        include: [path.resolve(__dirname, 'src/assets/icons')],
      },
      {
        test: /\.(js|jsx)$/,
        exclude: /node_modules/,
        use: 'babel-loader',
      },
      {
        test: /\.scss$/, // Aplica a regra a arquivos .scss
        use: [
          'style-loader', // Insere o CSS no DOM
          'css-loader',   // Processa os arquivos CSS
          'sass-loader',  // Converte SCSS para CSS
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
