package annotation;

import model.EntityTypeModel;
import model.EntityModelContext;

public interface TypeDecorator {

    void updateModel(EntityTypeModel model, EntityModelContext context);

}

