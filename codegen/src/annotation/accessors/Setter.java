package annotation.accessors;

import annotation.EntityFieldDecorator;
import annotation.EntityTypeDecorator;
import annotation.FieldDecorator;
import annotation.TypeDecorator;
import generation.TargetOutput;
import generation.writer.members.cpp.MembersWriterCppDecl;
import model.EntityTypeModel;
import model.EntityModelContext;
import generation.writer.accessors.cpp.AccessorWriterCppDecl;
import generation.writer.accessors.cpp.AccessorWriterCppDef;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.FIELD)
@Retention(RetentionPolicy.RUNTIME)
@EntityFieldDecorator(decorators = Setter.Decorator.class)
public @interface Setter {

    class Decorator implements FieldDecorator {
        @Override
        public void updateModel(EntityTypeModel model, EntityModelContext context) {
            model.addWriter(TargetOutput.HPP, new AccessorWriterCppDecl());
            model.addWriter(TargetOutput.CPP, new AccessorWriterCppDef());

            model.addWriter(TargetOutput.HPP, new MembersWriterCppDecl());
        }
    }
}
