
tic
    im=im2double(imread("GaussianNoise.jpg"));
    %dimensione del filtro
    filter_size=5;
    %media
    filtro_media=fspecial('average', filter_size);
    im_avg=imfilter(im, filtro_media, 'conv', 'circular');
    imwrite(im_avg,"GaussianRestoredMat.jpg");
time10 = toc;