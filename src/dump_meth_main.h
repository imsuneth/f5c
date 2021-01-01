#include <sys/stat.h>
#include <sys/types.h>

void dump_no_of_batches(int32_t no_of_batches) {
    const char *dump_dir = "dump_test";
    mkdir(dump_dir, 0700);
    char filename[100];
    FILE *fp;

    // no_of_batches
    snprintf(filename, sizeof(filename), "%s/%s", dump_dir,
             "no_of_batches.dat");
    fp = fopen(filename, "w");
    fwrite(&(no_of_batches), sizeof(int32_t), 1, fp);
    fclose(fp);
}

void dump_batch_info(core_t *core, db_t *db) {
    const char *dump_dir = "dump_test";
    mkdir(dump_dir, 0700);
    char batch_dir[50];
    snprintf(batch_dir, sizeof(batch_dir), "%s/%d", dump_dir, db->batch_no);
    mkdir(batch_dir, 0700);
    char filename[100];
    FILE *fp;

    // db->n_bam_rec
    snprintf(filename, sizeof(filename), "%s/%s", batch_dir, "n_bam_rec.dat");
    fp = fopen(filename, "w");
    fwrite(&(db->n_bam_rec), sizeof(int32_t), 1, fp);
    fclose(fp);

    // core->model - models
    snprintf(filename, sizeof(filename), "%s/%s", batch_dir, "model.dat");
    fp = fopen(filename, "w");
    fwrite(core->model, sizeof(model_t), NUM_KMER, fp);
    fclose(fp);
}
