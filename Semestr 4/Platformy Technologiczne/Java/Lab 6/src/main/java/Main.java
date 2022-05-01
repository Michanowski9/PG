import org.apache.commons.lang3.tuple.Pair;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ForkJoinPool;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Main {
    public static void main(String[] args) throws IOException {
        List<Path> files = new ArrayList<>();

        Path source = Path.of("src/main/resources/InputFiles");
        Path destSimple = Path.of("src/main/resources/OutputFiles/single");
        Path destParallel = Path.of("src/main/resources/OutputFiles/parallel");

        //get images to process
        try (Stream<Path> stream = Files.list(source)){
            files = stream.collect(Collectors.toList());
        }
        catch (IOException e) {
            e.printStackTrace();
        }

        long time;

        //with simple stream
        time = System.currentTimeMillis();
        simpleStreamUse(files, destSimple);
        System.out.println("simple stream time:\t\t" + (float)(System.currentTimeMillis() - time)/1000 + "s");

        //with parallel stream
        time = System.currentTimeMillis();
        parallelStreamUse(files, destParallel, 4);
        System.out.println("parallel stream time:\t" + (float)(System.currentTimeMillis() - time)/1000 + "s");

    }
    public static void simpleStreamUse(List<Path> files, Path dest){
        files.stream().map(Main::getPair).map(Main::processImage).forEach(c->save(c, dest));
    }
    public static void parallelStreamUse(List<Path> files, Path dest, int threads){
        ForkJoinPool pool = new ForkJoinPool(threads);
        try {
            pool.submit(() -> {
                files.parallelStream().map(Main::getPair).map(Main::processImage).forEach(c->save(c, dest));
            }).get();
        } catch (InterruptedException | ExecutionException ignored) {
        }
        pool.shutdown();
    }
    public static Pair<Path, BufferedImage> getPair(Path c) {
        BufferedImage image = null;
        try {
            image = ImageIO.read(c.toFile());
        } catch (IOException e) {
            e.printStackTrace();
        }

        return Pair.of(c, image);
    }
    public static Pair<Path, BufferedImage> processImage(Pair<Path, BufferedImage> original){
        BufferedImage newImage = new BufferedImage(
                original.getValue().getHeight(),
                original.getValue().getWidth(),
                original.getValue().getType());

        //processing
        //rotating image by 90 degrees
        //and changing pixels
        for (int i = 0; i < original.getValue().getWidth(); i++) {
            for (int j = 0; j < original.getValue().getHeight(); j++) {
                int rgb = original.getValue().getRGB(i, j);

                Color in = new Color(rgb);
                int red = 255 - (int) (in.getRed() * 0.3);
                int green = 255 - (int) (in.getGreen() * 0.3);
                int blue = 255 - (int) (in.getBlue() * 0.3);
                Color out = new Color(red, green, blue);

                newImage.setRGB(j, i, out.getRGB());
            }
        }

        return Pair.of(original.getKey(), newImage);
    }
    public static void save(Pair<Path, BufferedImage> image, Path dest){
        try {
            File outputFile = new File(dest.toString(), image.getKey().getFileName().toString());
            //System.out.println(outputFile.toString());

            ImageIO.write(image.getValue(), "jpg", outputFile);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
