const HtmlWebpackPlugin = require('html-webpack-plugin');
const path = require('path');
const { BundleAnalyzerPlugin } = require('webpack-bundle-analyzer');
const CopyWebpackPlugin = require('copy-webpack-plugin');
const mkdirp = require('mkdirp'); // Importa mkdirp

// Cria a pasta ./dist/assets/uploads antes de rodar o Webpack
mkdirp.sync(path.resolve(__dirname, 'dist/dist/assets/uploads'));

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
        test: /\.scss$/,
        use: [
          { loader: 'style-loader' },
          { loader: 'css-loader' },
          {
            loader: 'sass-loader',
            options: {
              implementation: require('sass'),
              sassOptions: {
                includePaths: [path.resolve(__dirname, 'src')],
              },
            },
          },
        ],
      },
      {
        test: /\.css$/,
        use: ['style-loader', 'css-loader'],
      },
    ],
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: path.resolve(__dirname, 'dist', 'index.html'),
      inject: false,
    }),
    new CopyWebpackPlugin({
      patterns: [
        { from: './src/style', to: '' },
      ],
    }),
    // new BundleAnalyzerPlugin(),
  ],
  devServer: {
    static: path.resolve(__dirname, 'dist'),
    port: 3000,
    hot: true,
    open: true,
  },
  resolve: {
    extensions: ['.js', '.jsx', '.scss', '.css'],
    alias: {
      '@emotion/react': require.resolve('@emotion/react'),
    },
  },
  optimization: {
    usedExports: true,
    minimize: true,
  },
};
