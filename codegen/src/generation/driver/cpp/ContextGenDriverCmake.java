package generation.driver.cpp;

import com.google.common.collect.ImmutableSet;
import generation.driver.ContextGenDriver;
import generation.driver.FilesystemHelper;
import generation.writer.helper.WriterHelperCpp;
import model.EntityModelContext;

import java.io.File;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashSet;
import java.util.Set;

public class ContextGenDriverCmake extends ContextGenDriver {

    public ContextGenDriverCmake(String outDir) {
        super(outDir);
    }

    @Override
    public Set<String> generate(EntityModelContext context) {
        StringBuffer cmake = new StringBuffer();
        buildCMAKE(context, cmake);

        FilesystemHelper.setFile(getOutDir(), "CMakeLists.txt", cmake.toString());

        return ImmutableSet.of(Paths.get(getOutDir(), "CMakeLists.txt").toString());
    }

    void buildCMAKE(EntityModelContext entityModelContext, StringBuffer buffer) {
        String module = entityModelContext.getProjectName();
        buffer.append("cmake_minimum_required (VERSION 2.6)" +  WriterHelperCpp.EOL);
        buffer.append("project ("+module+")" +  WriterHelperCpp.EOL);

        buffer.append(WriterHelperCpp.EOL);
        buffer.append("# The version number." + WriterHelperCpp.EOL +
                "set ("+module+"_VERSION_MAJOR 1)" + WriterHelperCpp.EOL +
                "set ("+module+"_VERSION_MINOR 0)" + WriterHelperCpp.EOL);

        buffer.append(WriterHelperCpp.EOL);
        buffer.append("# add the binary tree to the search path for include files" + WriterHelperCpp.EOL +
                "# so that we will find TutorialConfig.h" + WriterHelperCpp.EOL +
                "include_directories(\"${PROJECT_BINARY_DIR}\")" + WriterHelperCpp.EOL);

        buffer.append(WriterHelperCpp.EOL);
        buffer.append("# add the executable" + WriterHelperCpp.EOL +
                "add_executable("+module+" tutorial.cxx)");
    }

}
