#include <iostream>
#include "ogrsf_frmts.h"
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include "gdal.h"
#include <fstream>
#include <algorithm>

using namespace std;

bool myFunction(pair<boost::geometry::model::box<boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>>, int> i, pair<boost::geometry::model::box<boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>>, int> j) { return (i.second < j.second); }

int main(int argc, char* argv[]) {

    if (argc == 4) {

        GDALAllRegister();
        string pathToRead, pathToWrite;
        string pathToGetData;

        pathToGetData = argv[1];
        pathToRead = argv[2];
        pathToWrite = argv[3];

        double x_min, y_min, x_max, y_max;

        ifstream in(pathToRead);
        in >> x_min >> y_min >> x_max >> y_max;

        in.close();

        GDALDataset* dataset = static_cast<GDALDataset*>(GDALOpenEx(pathToGetData.c_str(),
            GDAL_OF_VECTOR,
            nullptr, nullptr, nullptr));

        auto point1 = boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>(x_min, y_min);
        auto point2 = boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>(x_max, y_max);
        auto rtree = boost::geometry::index::rtree<pair<boost::geometry::model::box<boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>>, int>, boost::geometry::index::quadratic<8, 4>>();

        for (auto&& layer : dataset->GetLayers()) {
            for (auto&& feature : layer) {

                auto* geometry = feature->GetGeometryRef();
                auto polygon2 = geometry->toPolygon();

                const shared_ptr<OGREnvelope> polygon2Envelope(new OGREnvelope);
                polygon2->getEnvelope(polygon2Envelope.get());

                auto point3 = boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>(polygon2Envelope->MinX, polygon2Envelope->MinY);
                auto point4 = boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>(polygon2Envelope->MaxX, polygon2Envelope->MaxY);

                auto box = boost::geometry::model::box<boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>>(point3, point4);

                auto value = pair<boost::geometry::model::box<boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>>, int>(box, feature->GetFieldAsInteger(0));

                rtree.insert(value);
            }
        }

        auto box = boost::geometry::model::box<boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>>(point1, point2);

        vector <pair<boost::geometry::model::box<boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>>, int>> vector;

        rtree.query(boost::geometry::index::intersects(box), back_inserter(vector));

        ofstream out(pathToWrite);

        std::sort(vector.begin(), vector.end(), myFunction);

        for (int i = 0; i < vector.size(); ++i) {
            out << vector.at(i).second << endl;
        }

        out.close();
    }
    else {
        cout << "Params are incorrect. Try again.";
    }
}