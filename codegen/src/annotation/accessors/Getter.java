package annotation.accessors;

import annotation.EntityFieldDecorator;
import annotation.FieldDecorator;
import generation.TargetOutput;
import generation.writer.members.cpp.MembersWriterCppDecl;
import model.EntityTypeModel;
import model.EntityModelContext;
import generation.writer.accessors.cpp.AccessorWriterCppDecl;
import generation.writer.accessors.cpp.AccessorWriterCppDef;

import java.lang.annotation.*;

@Target(ElementType.FIELD)
@Retention(RetentionPolicy.RUNTIME)
@EntityFieldDecorator(decorators = Getter.Decorator.class)
public @interface Getter {

    class Decorator implements FieldDecorator {
        @Override
        public void updateModel(EntityTypeModel model, EntityModelContext context) {
            model.addWriter(TargetOutput.HPP, new AccessorWriterCppDecl());
            model.addWriter(TargetOutput.CPP, new AccessorWriterCppDef());

            model.addWriter(TargetOutput.HPP, new MembersWriterCppDecl());
        }
    }
}
