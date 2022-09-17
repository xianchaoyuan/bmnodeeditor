#include "nodedata.h"
#include "flowscene.h"
#include "flowview.h"
#include "imageloadermodel.h"
#include "imageshowmodel.h"

#include <QApplication>

static std::shared_ptr<DataModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<DataModelRegistry>();
    ret->registerModel<ImageShowModel>();
    ret->registerModel<ImageLoaderModel>();

    return ret;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FlowScene scene(registerDataModels());
    FlowView view(&scene);

    view.setWindowTitle("Node-based flow editor");
    view.resize(800, 600);
    view.show();

    return app.exec();
}
