import compiler.RuntimeCompiler;
import generation.CodeGenDriver;
import generation.TargetOutput;
import model.EntityModelContext;
import model.EntityModelFactory;
import reflection.Collector;

import java.net.URL;
import java.nio.file.Paths;
import java.util.Set;

public class Main {

    public static void main(String[] varArgs) {
        System.out.println("Starting up");

        try {
            Arguments args = Arguments.parse(varArgs);
            process(args);
        }
        catch (IllegalArgumentException ex){
            ex.printStackTrace();
            System.exit(-1);
        }
        catch (Exception ex){
            ex.printStackTrace();
            System.exit(-1);
        }
        System.out.println("Exiting gracefully.");
        System.exit(0);
    }

    private static void process(Arguments args) throws Exception {

        System.out.println("File collection...");

        System.out.println("File collection: Done.");

        System.out.println("Compiling data model..");
        RuntimeCompiler compiler = new RuntimeCompiler(args.getTmpBuildDir());
        compiler.buildDir(args.getEntityModelsRootDir());
        System.out.println("Compiling data model: Done.");

        System.out.println("Code inspection...");
        URL builtClassesAsUrl = Paths.get(args.getTmpBuildDir()).toUri().toURL();
        Collector processor = new Collector(builtClassesAsUrl);
        Set<Class<?>> codeGenClasses = processor.collectCodeGenClasses();
        System.out.println("Code inspection: Done.");


        System.out.println("Building entity models...");
        EntityModelFactory genProcessor = new EntityModelFactory();
        EntityModelContext context = genProcessor.generate(codeGenClasses);
        System.out.println("Building entity models: Done.");

        System.out.println("Generating code in target lang...");
        CodeGenDriver codeGenerator = new CodeGenDriver(args.getOutputDir());
        codeGenerator.generate(args.getTargetOutput(), context);
        System.out.println("Generating code in target lang: Done.");
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////

}
