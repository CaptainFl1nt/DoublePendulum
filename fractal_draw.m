
times = csvread("fractal1000.csv");

width = length(times);
rgbMap = zeros(width,width,3);

for i = 1:width
    for j = 1:width
        if times(i,j) == -1
            rgbMap(i,j,1) = 1;
            rgbMap(i,j,2) = 1;
            rgbMap(i,j,3) = 1;
        elseif times(i,j) <= 3.0
            rgbMap(i,j,1) = 0;
            rgbMap(i,j,2) = 0.166667*times(i,j)+0.5;
            rgbMap(i,j,3) = 0;
        elseif (times(i,j) > 3.0) && (times(i,j) <= 10.0)
            rgbMap(i,j,1) = 0.0714286 * times(i,j) + 0.285714;
            rgbMap(i,j,2) = 0;
            rgbMap(i,j,3) = 0;
        else
            rgbMap(i,j,1) = 0;
            rgbMap(i,j,2) = 0;
            rgbMap(i,j,3) = 0.00142857*times(i,j) + 0.485714;
        end
    end
end

imwrite(rgbMap,"fractal_6.png")