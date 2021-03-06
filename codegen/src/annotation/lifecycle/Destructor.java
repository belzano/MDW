package annotation.lifecycle;

import annotation.EntityTypeDecorator;
import annotation.TypeDecorator;
import generation.TargetOutput;
import generation.writer.lifecycle.cpp.LifecycleWriterCppDecl;
import generation.writer.lifecycle.cpp.LifecycleWriterCppDef;
import generation.writer.members.cpp.MembersWriterCppDecl;
import model.EntityTypeModel;
import model.EntityModelContext;

import java.lang.annotation.ElementType;
import java.lang.annotation.Target;

@Target(ElementType.TYPE)
@EntityTypeDecorator(decorators = Destructor.Decorator.class)
public @interface Destructor {

    class Decorator implements TypeDecorator {
        @Override
        public void updateModel(EntityTypeModel model, EntityModelContext context) {
            model.addWriter(TargetOutput.HPP, new LifecycleWriterCppDecl());
            model.addWriter(TargetOutput.CPP, new LifecycleWriterCppDef());

            model.addWriter(TargetOutput.HPP, new MembersWriterCppDecl());
        }
    }
}
